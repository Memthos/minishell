/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 10:47:21 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/01 14:51:37 by juperrin         ###   ########.fr       */
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
		if (WIFSIGNALED(shell->exitno))
			shell->exitno = WTERMSIG(shell->exitno) + 128;
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
	if (NULL != shell->cur_cmd)
		free(shell->cur_cmd);
	if (NULL != shell->pids.pids)
		free(shell->pids.pids);
	ft_close(&shell->redirects.output_redirect_fd);
	ft_close(&shell->redirects.output_cmp_redirect_fd);
	ft_close(&shell->redirects.input_redirect_fd);
	ft_close(&shell->redirects.input_cmp_redirect_fd);
	ft_close(&shell->pipes.left_pipe[0]);
	ft_close(&shell->pipes.left_pipe[1]);
	ft_close(&shell->pipes.right_pipe[0]);
	ft_close(&shell->pipes.right_pipe[1]);
	ft_close(&shell->pipes.left_cmp_pipe[0]);
	ft_close(&shell->pipes.left_cmp_pipe[1]);
	ft_close(&shell->pipes.right_cmp_pipe[0]);
	ft_close(&shell->pipes.right_cmp_pipe[1]);
	ft_close(&shell->redirects.stdin_dup);
	ft_close(&shell->redirects.stdout_dup);
	dict_clear(&shell->env);
	cmds_lst_clear(&shell->cmd_ast);
	rl_clear_history();
	free(shell);
	return ;
}
