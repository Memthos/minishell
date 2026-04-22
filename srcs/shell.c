/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 10:47:21 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/22 14:38:38 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_status	wait_process(pid_t pid)
{
	t_status	status;

	if (pid < 0)
		return (SUCCESS);
	status = SUCCESS;
	if (waitpid(pid, (int *)&status, 0) < 0)
		perror("waitpid");
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		status = WTERMSIG(status) + 128;
	return (status);
}

t_status	wait_for_processes(t_pids_logic *pids)
{
	t_status	status;

	if (NULL == pids || NULL == pids->pids || 0 == pids->pid_count)
		return (SUCCESS);
	status = SUCCESS;
	pids->pid_index = 0;
	while (pids->pid_index < pids->pid_count)
	{
		status = wait_process(pids->pids[pids->pid_index]);
		++pids->pid_index;
	}
	if (status >= 128)
	{
		if (SIGQUIT + 128 == status)
			printf("Quit");
		printf("\n");
	}
	free(pids->pids);
	pids->pids = NULL;
	pids->pid_count = 0;
	return (status);
}

void	close_redirections(t_shell *shell)
{
	ft_close(&shell->redirects.output_fd);
	ft_close(&shell->redirects.output_cmp_fd);
	ft_close(&shell->redirects.input_fd);
	ft_close(&shell->redirects.input_cmp_fd);
	return ;
}

void	destroy_shell(t_shell *shell, bool keep_pids)
{
	if (NULL == shell)
		return ;
	rl_clear_history();
	stack_lst_clear(&shell->pipe_stack, (void (*)(void *)) & pipe_close);
	free(shell->cur_cmd);
	if (!keep_pids)
		free(shell->pids.pids);
	close_redirections(shell);
	ft_close(&shell->redirects.stdin_dup);
	ft_close(&shell->redirects.stdout_dup);
	cmds_lst_clear(&shell->cmd_ast);
	dict_clear(&shell->env);
	free(shell);
	return ;
}
