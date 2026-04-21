/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 10:54:56 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/21 15:52:47 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_status	cur_cmd_init(t_ast_lst *cmd, t_shell *shell)
{
	shell->cur_cmd_index = 0;
	shell->cur_cmd = malloc(sizeof(t_string) * (ast_cmd_size(cmd) + 1));
	if (NULL == shell->cur_cmd)
	{
		perror("malloc");
		shell->exitno = FAILURE;
		return (shell->exitno);
	}
	return (SUCCESS);
}

static t_status	execute_word(t_ast_lst *cmd, t_shell *shell)
{
	execute(cmd->left, shell);
	if (SUCCESS != shell->exitno)
		return (shell->exitno);
	if (NULL == shell->cur_cmd)
		if (SUCCESS != cur_cmd_init(cmd, shell))
			return (FAILURE);
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
	return (shell->exitno);
}

static t_status	execute_pipe(t_ast_lst *cmd, t_shell *shell)
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
	return (shell->exitno);
}

static t_status	open_redirection(int *fd, t_string name, t_uint flags)
{
	*fd = open(name, flags, 0644);
	if (-1 == *fd)
	{
		error_output(name, strerror(errno), NO_ERR_MSG);
		return (FAILURE);
	}
	return (SUCCESS);
}

static t_status	execute_out_redirection(t_ast_lst *cmd, t_shell *shell)
{
	ft_close(&shell->redirects.output_fd);
	if (shell->redirects.is_cmp_redir)
		ft_close(&shell->redirects.output_cmp_fd);
	if (cmd->left->token == AMB_RED)
	{
		amb_red_error_print(cmd->left->data);
		shell->exitno = FAILURE;
		return (shell->exitno);
	}
	if (SUCCESS != open_redirection(&shell->redirects.output_fd, cmd->left->data,
			O_WRONLY | O_CREAT
			| O_APPEND * (DGREAT == cmd->token)
			| O_TRUNC * (DGREAT != cmd->token)))
	{
		shell->exitno = FAILURE;
		return (shell->exitno);
	}
	if (shell->redirects.is_cmp_redir)
	{
		shell->redirects.output_cmp_fd = shell->redirects.output_fd;
		shell->redirects.output_fd = -1;
	}
	execute(cmd->left->left, shell);
	return (shell->exitno);
}

static t_status	execute_in_redirection(t_ast_lst *cmd, t_shell *shell)
{
	ft_close(&shell->redirects.input_fd);
	if (shell->redirects.is_cmp_redir)
		ft_close(&shell->redirects.input_cmp_fd);
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
	if (SUCCESS != open_redirection(&shell->redirects.input_fd, cmd->left->data, O_RDONLY))
	{
		shell->exitno = FAILURE;
		return (shell->exitno);
	}
	if (shell->redirects.is_cmp_redir)
	{
		shell->redirects.input_cmp_fd = shell->redirects.input_fd;
		shell->redirects.input_fd = -1;
	}
	execute(cmd->left->left, shell);
	return (shell->exitno);
}

static t_status	execute_heredoc(t_ast_lst *cmd, t_shell *shell)
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
	return (shell->exitno);
}

static t_status	execute_cmd_list(t_ast_lst *cmd, t_shell *shell)
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
	return (shell->exitno);
}

static t_status	execute_parentheses(t_ast_lst *cmd, t_shell *shell)
{
	++shell->cmp_depth;
	shell->redirects.is_cmp_redir = true;
	execute(cmd->right, shell);
	shell->redirects.is_cmp_redir = false;
	execute(cmd->left, shell);
	ft_close(&shell->redirects.output_cmp_fd);
	ft_close(&shell->redirects.input_cmp_fd);
	--shell->cmp_depth;
	return (shell->exitno);
}

t_status	execute(t_ast_lst *cmd, t_shell *shell)
{
	if (NULL == cmd)
		return (shell->exitno);
	if (WORD == cmd->token)
		return (execute_word(cmd, shell));
	if (PIPE == cmd->token)
		return (execute_pipe(cmd, shell));
	if (GREAT == cmd->token || DGREAT == cmd->token)
		return (execute_out_redirection(cmd, shell));
	if (LESS == cmd->token)
		return (execute_in_redirection(cmd, shell));
	if (DLESS == cmd->token)
		return (execute_heredoc(cmd, shell));
	if (AND_IF == cmd->token || OR_IF == cmd->token)
		return (execute_cmd_list(cmd, shell));
	if (CMP_CMD == cmd->token)
		return (execute_parentheses(cmd, shell));
	return (shell->exitno);
}
