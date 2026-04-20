/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 10:47:21 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/20 13:08:04 by juperrin         ###   ########.fr       */
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
	waitpid(pid, (int *)&status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		status = WTERMSIG(status) + 128;
	return (status);
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
		shell->exitno = wait_process(shell->pids.pids[shell->pids.pid_index]);
		++shell->pids.pid_index;
	}
	if (shell->exitno >= 128)
	{
		if (SIGQUIT + 128 == shell->exitno)
			printf("Quit");
		printf("\n");
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
	rl_clear_history();
	stack_lst_clear(&shell->pipe_stack, (void (*)(void *)) & pipe_close);
	free(shell->cur_cmd);
	free(shell->pids.pids);
	ft_close(&shell->redirects.output_redirect_fd);
	ft_close(&shell->redirects.output_cmp_redirect_fd);
	ft_close(&shell->redirects.input_redirect_fd);
	ft_close(&shell->redirects.input_cmp_redirect_fd);
	ft_close(&shell->redirects.stdin_dup);
	ft_close(&shell->redirects.stdout_dup);
	cmds_lst_clear(&shell->cmd_ast);
	dict_clear(&shell->env);
	free(shell);
	return ;
}
