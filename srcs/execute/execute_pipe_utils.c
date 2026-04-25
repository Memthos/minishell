/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 21:07:33 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/25 14:20:04 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	execute_pipe(t_ast_lst *cmd, t_shell *shell)
{
	t_status	status;
	int			pipes[2];
	pid_t		fork_pids[2];

	pipe(pipes);
	fork_pids[0] = fork();
	if (0 == fork_pids[0])
	{
		close(pipes[0]);
		redirect_output(&pipes[1]);
		execute(cmd->left, shell);
		status = shell->exitno;
		destroy_shell(shell, false);
		exit(status);
	}
	fork_pids[1] = fork();
	if (0 == fork_pids[1])
	{
		close(pipes[1]);
		redirect_input(&pipes[0]);
		execute(cmd->right, shell);
		status = shell->exitno;
		destroy_shell(shell, false);
		exit(status);
	}
	ft_close(&pipes[0]);
	ft_close(&pipes[1]);
	shell->exitno = wait_process(fork_pids[0]);
	shell->exitno = wait_process(fork_pids[1]);
	return (shell->exitno);
}
