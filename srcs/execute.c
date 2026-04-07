/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 10:54:56 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/07 15:50:42 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_status	execute(t_ast_lst *cmd, t_shell *shell)
{
	int	*cur_pipe;

	if (NULL == cmd)
		return (shell->exitno);
	if (WORD == cmd->token)
	{
		execute(cmd->left, shell);
		if (128 + SIGPIPE == shell->exitno)
			return (shell->exitno);
		if (NULL == shell->cur_cmd)
		{
			shell->cur_cmd_index = 0;
			shell->cur_cmd = malloc(sizeof(char *) * (ast_cmd_size(cmd) + 1));
			if (NULL == shell->cur_cmd)
			{
				perror("malloc");
				shell->exitno = FAILURE;
				return (shell->exitno);
			}
		}
		shell->cur_cmd[shell->cur_cmd_index] = cmd->data;
		++shell->cur_cmd_index;
		if (NULL == cmd->right)
		{
			shell->cur_cmd[shell->cur_cmd_index] = NULL;
			shell->exitno = execute_cmd(shell);
			free(shell->cur_cmd);
			shell->cur_cmd = NULL;
			return (shell->exitno);
		}
		execute(cmd->right, shell);
	}
	if (PIPE == cmd->token)
	{
		++shell->pipes.pipe_depth;
		if (!ast_pipe_count(cmd->left))
		{
			if (-1 == pipe(get_cur_pipe(&shell->pipes, false, false)))
			{
				perror("pipe");
				shell->exitno = FAILURE;
				return (shell->exitno);
			}
			shell->pipes.redirect_output = true;
		}
		execute(cmd->left, shell);
		shell->pipes.redirect_output = false;
		++shell->pipes.pipe_index;
		if (shell->pipes.pipe_depth > 1)
		{
			if (-1 == pipe(get_cur_pipe(&shell->pipes, false, false)))
			{
				perror("pipe");
				shell->exitno = FAILURE;
				return (shell->exitno);
			}
			shell->pipes.redirect_output = true;
		}
		shell->pipes.redirect_input = true;
		execute(cmd->right, shell);
		shell->pipes.redirect_input = false;
		cur_pipe = get_cur_pipe(&shell->pipes, true, false);
		ft_close(&cur_pipe[0]);
		ft_close(&cur_pipe[1]);
		--shell->pipes.pipe_depth;
	}
	if (GREAT == cmd->token || DGREAT == cmd->token)
	{
		ft_close(&shell->redirects.output_redirect_fd);
		shell->redirects.out_flags = O_WRONLY | O_CREAT;
		if (DGREAT == cmd->token)
			shell->redirects.out_flags |= O_APPEND;
		else
			shell->redirects.out_flags |= O_TRUNC;
		shell->redirects.output_redirect_fd = open(cmd->left->data,
				shell->redirects.out_flags, 0644);
		if (-1 == shell->redirects.output_redirect_fd)
		{
			perror("open");
			shell->exitno = FAILURE;
			return (shell->exitno);
		}
		if (shell->redirects.is_cmp_redir)
		{
			ft_close(&shell->redirects.output_cmp_redirect_fd);
			shell->redirects.output_cmp_redirect_fd = shell->redirects.output_redirect_fd;
			shell->redirects.output_redirect_fd = -1;
		}
		execute(cmd->left->left, shell);
	}
	if (LESS == cmd->token)
	{
		if (access(cmd->left->data, F_OK) < 0)
		{
			error_output(NULL, cmd->left->data, FILE_NOT_FOUND);
			shell->exitno = FAILURE;
			return (FAILURE);
		}
		else if (access(cmd->left->data, R_OK) < 0)
		{
			error_output(NULL, cmd->left->data, PERMISSION_ERROR);
			shell->exitno = FAILURE;
			return (FAILURE);
		}
		ft_close(&shell->redirects.input_redirect_fd);
		shell->redirects.in_flags = O_RDONLY;
		shell->redirects.input_redirect_fd = open(cmd->left->data,
				shell->redirects.in_flags);
		if (-1 == shell->redirects.input_redirect_fd)
		{
			perror("open");
			shell->exitno = FAILURE;
			return (shell->exitno);
		}
		if (shell->redirects.is_cmp_redir)
		{
			ft_close(&shell->redirects.input_cmp_redirect_fd);
			shell->redirects.input_cmp_redirect_fd = shell->redirects.input_redirect_fd;
			shell->redirects.input_redirect_fd = -1;
		}
		execute(cmd->left->left, shell);
	}
	if (DLESS == cmd->token)
	{
		if (ast_heredoc_count(cmd, shell->redirects.is_cmp_redir)
			> shell->heredoc_max)
		{
			error_output(NULL, NULL, HEREDOC_COUNT_EXCEEDED);
			shell->exitno = BAD_ARG;
			return (shell->exitno);
		}
		if (heredoc(shell, cmd))
		{
			error_output(NULL, NULL, shell->exitno);
			return (shell->exitno);
		}
		execute(cmd->left->left, shell);
	}
	if (AND_IF == cmd->token || OR_IF == cmd->token)
	{
		execute(cmd->left, shell);
		wait_for_processes(shell);
		if (final_parsing(shell, &cmd->right))
			return (shell->exitno);
		if (AND_IF == cmd->token && SUCCESS == shell->exitno)
			execute(cmd->right, shell);
		if (OR_IF == cmd->token && SUCCESS != shell->exitno)
			execute(cmd->right, shell);
	}
	if (CMP_CMD == cmd->token)
	{
		++shell->cmp_depth;
		shell->redirects.is_cmp_redir = true;
		execute(cmd->right, shell);
		shell->redirects.is_cmp_redir = false;
		execute(cmd->left, shell);
		ft_close(&shell->redirects.output_cmp_redirect_fd);
		ft_close(&shell->redirects.input_cmp_redirect_fd);
		--shell->cmp_depth;
	}
	return (shell->exitno);
}

t_status	execute_cmd(t_shell *shell)
{
	t_status	code;
	pid_t		pid;
	int			*output_pipe;
	int			*input_pipe;
	t_built_in	cmd;

	if (NULL == shell || NULL == shell->cur_cmd || 0 == shell->cur_cmd_index)
		return (FAILURE);
	cmd = get_command(*shell->cur_cmd);
	if (0 == shell->pipes.pipe_depth && &cmd_exec != cmd)
	{
		if (-1 != shell->redirects.output_redirect_fd)
		{
			if (-1 == dup2(shell->redirects.output_redirect_fd, STDOUT_FILENO))
			{
				perror("dup2");
				ft_close(&shell->redirects.output_redirect_fd);
				shell->exitno = DUP_FAILURE;
				return (shell->exitno);
			}
			ft_close(&shell->redirects.output_redirect_fd);
		}
		else if (-1 != shell->redirects.output_cmp_redirect_fd)
		{
			if (-1 == dup2(shell->redirects.output_cmp_redirect_fd, STDOUT_FILENO))
			{
				perror("dup2");
				ft_close(&shell->redirects.output_cmp_redirect_fd);
				shell->exitno = DUP_FAILURE;
				return (shell->exitno);
			}
			ft_close(&shell->redirects.output_cmp_redirect_fd);
		}
		shell->exitno = cmd(shell->cur_cmd, shell);
		if (-1 == dup2(shell->redirects.stdout_dup, STDOUT_FILENO))
		{
			perror("dup2");
			shell->exitno = DUP_FAILURE;
		}
		return (shell->exitno);
	}
	pid = fork();
	if (-1 == pid)
	{
		shell->exitno = FORK_FAILURE;
		return (FORK_FAILURE);
	}
	if (0 == pid)
	{
		restore_signals();
		ft_close(&shell->redirects.stdin_dup);
		ft_close(&shell->redirects.stdout_dup);
		output_pipe = get_cur_pipe(&shell->pipes, false, false);
		input_pipe = get_cur_pipe(&shell->pipes, true, false);
		if (shell->pipes.redirect_output)
		{
			if (-1 == dup2(output_pipe[1], STDOUT_FILENO))
			{
				perror("dup2");
				destroy_shell(shell);
				exit(DUP_FAILURE);
			}
			ft_close(&output_pipe[0]);
			ft_close(&output_pipe[1]);
		}
		if (shell->pipes.redirect_input)
		{
			if (-1 == dup2(input_pipe[0], STDIN_FILENO))
			{
				perror("dup2");
				destroy_shell(shell);
				exit(DUP_FAILURE);
			}
			ft_close(&input_pipe[0]);
			ft_close(&input_pipe[1]);
		}
		if (-1 != shell->redirects.input_redirect_fd)
		{
			if (-1 == dup2(shell->redirects.input_redirect_fd, STDIN_FILENO))
			{
				perror("dup2");
				destroy_shell(shell);
				exit(DUP_FAILURE);
			}
			ft_close(&shell->redirects.input_redirect_fd);
		}
		else if (-1 != shell->redirects.input_cmp_redirect_fd)
		{
			if (-1 == dup2(shell->redirects.input_cmp_redirect_fd, STDIN_FILENO))
			{
				perror("dup2");
				destroy_shell(shell);
				exit(DUP_FAILURE);
			}
			ft_close(&shell->redirects.input_cmp_redirect_fd);
		}
		if (-1 != shell->redirects.output_redirect_fd)
		{
			if (-1 == dup2(shell->redirects.output_redirect_fd, STDOUT_FILENO))
			{
				perror("dup2");
				destroy_shell(shell);
				exit(DUP_FAILURE);
			}
			ft_close(&shell->redirects.output_redirect_fd);
		}
		else if (-1 != shell->redirects.output_cmp_redirect_fd)
		{
			if (-1 == dup2(shell->redirects.output_cmp_redirect_fd, STDOUT_FILENO))
			{
				perror("dup2");
				destroy_shell(shell);
				exit(DUP_FAILURE);
			}
			ft_close(&shell->redirects.output_cmp_redirect_fd);
		}
		code = cmd(shell->cur_cmd, shell);
		destroy_shell(shell);
		exit(code);
	}
	ft_close(&shell->redirects.input_redirect_fd);
	ft_close(&shell->redirects.output_redirect_fd);
	shell->exitno = update_pids(shell, pid);
	return (shell->exitno);
}
