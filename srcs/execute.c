/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 10:54:56 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/20 21:47:21 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	execute(t_ast_lst *cmd, t_shell *shell)
{
	if (NULL == cmd)
		return (shell->exitno);
	if (WORD == cmd->token)
	{
		execute(cmd->left, shell);
		if (SUCCESS != shell->exitno)
			return (shell->exitno);
		if (NULL == shell->cur_cmd)
		{
			shell->cur_cmd_index = 0;
			shell->cur_cmd = malloc(sizeof(t_string) * (ast_cmd_size(cmd) + 1));
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
		t_status		code;
		pid_t			fork_pids[2];
		t_pids_logic	pid_logic;
		t_pipe			*_pipe;

		_pipe = pipe_new();
		stack_lst_append(&shell->pipe_stack, _pipe);
		++shell->redirect_output;
		fork_pids[0] = fork();
		if (0 == fork_pids[0])
		{
			execute(cmd->left, shell);
			code = shell->exitno;
			pid_logic.pid_count = shell->pids.pid_count;
			pid_logic.pids = malloc(sizeof(pid_t) * pid_logic.pid_count);
			ft_memcpy(pid_logic.pids, shell->pids.pids, sizeof(pid_t) * pid_logic.pid_count);
			destroy_shell(shell);
			code = wait_for_processes(&pid_logic);
			exit(code);
		}
		--shell->redirect_output;
		_pipe->side = RIGHT;
		++shell->redirect_input;
		fork_pids[1] = fork();
		if (0 == fork_pids[1])
		{
			execute(cmd->right, shell);
			code = shell->exitno;
			pid_logic.pid_count = shell->pids.pid_count;
			pid_logic.pids = malloc(sizeof(pid_t) * pid_logic.pid_count);
			ft_memcpy(pid_logic.pids, shell->pids.pids, sizeof(pid_t) * pid_logic.pid_count);
			destroy_shell(shell);
			code = wait_for_processes(&pid_logic);
			exit(code);
		}
		--shell->redirect_input;
		stack_lst_clear(&shell->pipe_stack, (void (*)(void *)) & pipe_close);
		shell->exitno = wait_process(fork_pids[0]);
		shell->exitno = wait_process(fork_pids[1]);
	}
	if (GREAT == cmd->token || DGREAT == cmd->token)
	{
		if (cmd->left->token == AMB_RED)
		{
			amb_red_error_print(cmd->left->data);
			shell->exitno = FAILURE;
			return (shell->exitno);
		}
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
			error_output(cmd->left->data, strerror(errno), NO_ERR_MSG);
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
		if (cmd->left->token == AMB_RED)
		{
			amb_red_error_print(cmd->left->data);
			shell->exitno = FAILURE;
			return (shell->exitno);
		}
		if (access(cmd->left->data, F_OK) < 0)
		{
			error_output(NULL, cmd->left->data, FILE_NOT_FOUND);
			shell->exitno = FAILURE;
			return (shell->exitno);
		}
		else if (access(cmd->left->data, R_OK) < 0)
		{
			error_output(NULL, cmd->left->data, PERMISSION_ERROR);
			shell->exitno = 126;
			return (shell->exitno);
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
		wait_for_processes(&shell->pids);
		shell->oldexitno = shell->exitno;
		if (final_parsing(shell, &cmd->right))
			return (shell->exitno);
		if (AND_IF == cmd->token && SUCCESS == shell->exitno)
			execute(cmd->right, shell);
		if (OR_IF == cmd->token && SUCCESS != shell->exitno)
		{
			shell->exitno = SUCCESS;
			execute(cmd->right, shell);
		}
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

static t_status	execute_simple_cmd(t_built_in cmd, t_shell *shell)
{
	bool	redirected;

	redirected = false;
	if (-1 != shell->redirects.output_redirect_fd)
	{
		redirected = true;
		redirect_output(&shell->redirects.output_redirect_fd);
	}
	else if (-1 != shell->redirects.output_cmp_redirect_fd)
	{
		redirected = true;
		redirect_output(&shell->redirects.output_cmp_redirect_fd);
	}
	shell->exitno = cmd(shell->cur_cmd, shell);
	if (redirected && dup2(shell->redirects.stdout_dup, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		shell->exitno = FAILURE;
		return (shell->exitno);
	}
	return (shell->exitno);
}

static t_status	execute_cmd_child_pipe(t_shell *shell)
{
	t_pipe	*input_pipe;
	t_pipe	*output_pipe;

	input_pipe = pipe_get(shell, RIGHT);
	output_pipe = pipe_get(shell, LEFT);
	if (input_pipe && shell->redirect_input)
	{
		if (SUCCESS != redirect_input(&input_pipe->pipe[0]))
		{
			destroy_shell(shell);
			exit(FAILURE);
		}
	}
	if (output_pipe && shell->redirect_output)
	{
		if (SUCCESS != redirect_output(&output_pipe->pipe[1]))
		{
			destroy_shell(shell);
			exit(FAILURE);
		}
	}
	stack_lst_clear(&shell->pipe_stack, (void (*)(void *)) & pipe_close);
	return (SUCCESS);
}

static t_status	execute_cmd_child_input_redirection(t_shell *shell)
{
	if (-1 != shell->redirects.input_redirect_fd)
	{
		if (SUCCESS != redirect_input(&shell->redirects.input_redirect_fd))
		{
			destroy_shell(shell);
			exit(FAILURE);
		}
	}
	else if (-1 != shell->redirects.input_cmp_redirect_fd)
	{
		if (SUCCESS != redirect_input(&shell->redirects.input_cmp_redirect_fd))
		{
			destroy_shell(shell);
			exit(FAILURE);
		}
	}
	return (SUCCESS);
}

static t_status	execute_cmd_child_output_redirection(t_shell *shell)
{
	if (-1 != shell->redirects.output_redirect_fd)
	{
		if (SUCCESS != redirect_output(&shell->redirects.output_redirect_fd))
		{
			destroy_shell(shell);
			exit(FAILURE);
		}
	}
	else if (-1 != shell->redirects.output_cmp_redirect_fd)
	{
		if (SUCCESS != redirect_output(&shell->redirects.output_cmp_redirect_fd))
		{
			destroy_shell(shell);
			exit(FAILURE);
		}
	}
	return (SUCCESS);
}

static t_status	execute_cmd_child(t_built_in cmd, t_shell *shell)
{
	t_status	status;
	
	restore_signals();
	ft_close(&shell->redirects.stdin_dup);
	ft_close(&shell->redirects.stdout_dup);
	execute_cmd_child_pipe(shell);
	execute_cmd_child_input_redirection(shell);
	execute_cmd_child_output_redirection(shell);
	status = cmd(shell->cur_cmd, shell);
	destroy_shell(shell);
	exit(status);
}

t_status	execute_cmd(t_shell *shell)
{
	pid_t		pid;
	t_built_in	cmd;

	if (NULL == shell || NULL == shell->cur_cmd || 0 == shell->cur_cmd_index)
		return (FAILURE);
	cmd = get_command(*shell->cur_cmd);
	if (&cmd_exec != cmd && 0 == stack_lst_size(shell->pipe_stack))
		return (execute_simple_cmd(cmd, shell));
	pid = fork();
	if (-1 == pid)
	{
		shell->exitno = FORK_FAILURE;
		return (FORK_FAILURE);
	}
	if (0 == pid)
		execute_cmd_child(cmd, shell);
	ft_close(&shell->redirects.input_redirect_fd);
	ft_close(&shell->redirects.output_redirect_fd);
	update_pids(shell, pid);
	return (shell->exitno);
}
