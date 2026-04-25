/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 21:07:33 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/25 16:05:41 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static pid_t	execute_pipe_left(t_ast_lst *cmd, t_shell *shell, int _pipe[2])
{
	pid_t		pid;
	t_status	status;

	pid = fork();
	if (-1 == pid)
	{
		perror("fork");
		--shell->pipe_depth;
		shell->exitno = FAILURE;
		return (-1);
	}
	if (0 == pid)
	{
		close(_pipe[0]);
		redirect_output(&_pipe[1]);
		execute(cmd->left, shell);
		status = shell->exitno;
		destroy_shell(shell, false);
		exit(status);
	}
	return (pid);
}

static pid_t	execute_pipe_right(t_ast_lst *cmd, t_shell *shell, int _pipe[2])
{
	pid_t		pid;
	t_status	status;

	pid = fork();
	if (-1 == pid)
	{
		perror("fork");
		--shell->pipe_depth;
		shell->exitno = FAILURE;
		return (-1);
	}
	if (0 == pid)
	{
		close(_pipe[1]);
		redirect_input(&_pipe[0]);
		execute(cmd->right, shell);
		status = shell->exitno;
		destroy_shell(shell, false);
		exit(status);
	}
	return (pid);
}

t_status	execute_pipe(t_ast_lst *cmd, t_shell *shell)
{
	int		_pipe[2];
	pid_t	pids[2];

	if (-1 == pipe(_pipe))
	{
		perror("pipe");
		shell->exitno = FAILURE;
		return (shell->exitno);
	}
	++shell->pipe_depth;
	pids[0] = execute_pipe_left(cmd, shell, _pipe);
	if (-1 == pids[0])
		return (FAILURE);
	pids[1] = execute_pipe_right(cmd, shell, _pipe);
	ft_close(&_pipe[0]);
	ft_close(&_pipe[1]);
	if (-1 == pids[1])
	{
		wait_process(pids[0]);
		return (FAILURE);
	}
	shell->exitno = wait_process(pids[0]);
	shell->exitno = wait_process(pids[1]);
	--shell->pipe_depth;
	return (shell->exitno);
}
