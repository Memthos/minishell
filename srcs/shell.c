/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 10:47:21 by juperrin          #+#    #+#             */
/*   Updated: 2026/03/13 10:52:53 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_status	update_pids(t_shell *shell, pid_t pid)
{
	if (NULL == shell || pid < 1)
		return (FAILURE);
	shell->pids = increment_array(shell->pids, shell->pid_count, sizeof(pid_t));
	if (NULL == shell->pids)
	{
		perror("malloc");
		shell->exitno = ALLOCATION_FAILURE;
		return (ALLOCATION_FAILURE);
	}
	shell->pids[shell->pid_count] = pid;
	++shell->pid_count;
	return (SUCCESS);
}

void	destroy_shell(t_shell *shell)
{
	if (NULL == shell)
		return ;
	if (NULL != shell->cur_cmd)
		free(shell->cur_cmd);
	if (NULL != shell->pids)
		free(shell->pids);
	ft_close(&shell->pipe1[0]);
	ft_close(&shell->pipe1[1]);
	ft_close(&shell->pipe2[0]);
	ft_close(&shell->pipe2[1]);
	dict_clear(&shell->env);
	dict_clear(&shell->locals);
	ast_lst_clear(&shell->cmd_ast);
	free(shell);
	dprintf(2, "Shell has been destroyed\n");
	return ;
}
