/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:06:10 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/25 14:13:45 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	execute_simple_cmd(t_built_in cmd, t_shell *shell);
t_status	execute_cmd_child(t_built_in cmd, t_shell *shell);

t_status	execute_cmd(t_shell *shell)
{
	pid_t		pid;
	t_built_in	cmd;

	if (NULL == shell || NULL == shell->cur_cmd || 0 == shell->cur_cmd_index)
		return (FAILURE);
	cmd = get_command(*shell->cur_cmd);
	if (&cmd_exec != cmd) // Add condition for pipe_depth
		return (execute_simple_cmd(cmd, shell));
	pid = fork();
	if (-1 == pid)
	{
		shell->exitno = FORK_FAILURE;
		return (FORK_FAILURE);
	}
	if (0 == pid)
		execute_cmd_child(cmd, shell);
	ft_close(&shell->redirects.input_fd);
	ft_close(&shell->redirects.output_fd);
	shell->exitno = wait_process(pid);
	return (shell->exitno);
}
