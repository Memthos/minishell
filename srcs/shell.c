/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 10:47:21 by juperrin          #+#    #+#             */
/*   Updated: 2026/03/13 13:53:59 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_status	update_pids(t_shell *shell, pid_t pid)
{
	if (NULL == shell || pid < 1)
		return (FAILURE);
	shell->pids.pids = increment_array(shell->pids.pids,
			shell->pids.pid_count, sizeof(pid_t));
	if (NULL == shell->pids.pids)
	{
		perror("malloc");
		shell->exitno = ALLOCATION_FAILURE;
		return (ALLOCATION_FAILURE);
	}
	shell->pids.pids[shell->pids.pid_count] = pid;
	++shell->pids.pid_count;
	return (SUCCESS);
}

t_status	wait_for_processes(t_shell *shell)
{
	if (NULL == shell)
		return (FAILURE);
	if (NULL == shell->pids.pids)
		return (SUCCESS);
	shell->pids.pid_index = 0;
	while (shell->pids.pid_index < shell->pids.pid_count)
	{
		waitpid(shell->pids.pids[shell->pids.pid_index],
			(int *)&shell->exitno, 0);
		if (WIFEXITED(shell->exitno))
			shell->exitno = WEXITSTATUS(shell->exitno);
		dprintf(2, "Process %d exited with status %d\n", shell->pids.pids[shell->pids.pid_index], shell->exitno);
		++shell->pids.pid_index;
	}
	free(shell->pids.pids);
	shell->pids.pids = NULL;
	shell->pids.pid_count = 0;
	return (shell->exitno);
}

void	destroy_shell(t_shell *shell)
{
	if (NULL == shell)
		return ;
	if (NULL != shell->cur_cmd)
		free(shell->cur_cmd);
	if (NULL != shell->pids.pids)
		free(shell->pids.pids);
	ft_close(&shell->pipes.pipe1[0]);
	ft_close(&shell->pipes.pipe1[1]);
	ft_close(&shell->pipes.pipe2[0]);
	ft_close(&shell->pipes.pipe2[1]);
	dict_clear(&shell->env);
	dict_clear(&shell->locals);
	ast_lst_clear(&shell->cmd_ast);
	free(shell);
	dprintf(2, "Shell has been destroyed\n");
	return ;
}
