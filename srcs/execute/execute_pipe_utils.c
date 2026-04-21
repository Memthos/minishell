/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 21:07:33 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/21 21:10:50 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_pipe	*append_new_pipe(t_shell *shell)
{
	t_pipe	*_pipe;

	_pipe = pipe_new();
	if (NULL == _pipe)
	{
		shell->exitno = FAILURE;
		return (NULL);
	}
	if (NULL == stack_lst_append(&shell->pipe_stack, _pipe))
	{
		pipe_close(_pipe);
		shell->exitno = FAILURE;
		return (NULL);
	}
	return (_pipe);
}

static t_status	execute_pipe_child(t_ast_lst *cmd, t_shell *shell)
{
	t_status		code;
	t_pids_logic	pid_logic;

	execute(cmd, shell);
	code = shell->exitno;
	pid_logic.pid_count = shell->pids.pid_count;
	pid_logic.pids = malloc(sizeof(pid_t) * pid_logic.pid_count);
	if (NULL == pid_logic.pids)
	{
		perror("malloc");
		destroy_shell(shell);
		exit(FAILURE);
	}
	ft_memcpy(pid_logic.pids, shell->pids.pids, 4 * pid_logic.pid_count);
	destroy_shell(shell);
	code = wait_for_processes(&pid_logic);
	exit(code);
}

static pid_t	execute_pipe_fork(t_ast_lst *cmd, t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (-1 == pid)
	{
		stack_lst_clear(&shell->pipe_stack, (void (*)(void *)) & pipe_close);
		shell->exitno = FAILURE;
		return (-1);
	}
	if (0 == pid)
		execute_pipe_child(cmd, shell);
	return (pid);
}

t_status	execute_pipe(t_ast_lst *cmd, t_shell *shell)
{
	t_pipe	*_pipe;
	pid_t	fork_pids[2];

	_pipe = append_new_pipe(shell);
	if (NULL == _pipe)
		return (FAILURE);
	++shell->redirect_output;
	fork_pids[0] = execute_pipe_fork(cmd->left, shell);
	--shell->redirect_output;
	if (fork_pids[0] < 0)
		return (shell->exitno);
	_pipe->side = RIGHT;
	++shell->redirect_input;
	fork_pids[1] = execute_pipe_fork(cmd->right, shell);
	--shell->redirect_input;
	if (fork_pids[1] < 0)
	{
		shell->exitno = wait_process(fork_pids[0]);
		return (shell->exitno);
	}
	stack_lst_clear(&shell->pipe_stack, (void (*)(void *)) & pipe_close);
	shell->exitno = wait_process(fork_pids[0]);
	shell->exitno = wait_process(fork_pids[1]);
	return (shell->exitno);
}
