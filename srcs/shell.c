/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 10:47:21 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/30 11:12:16 by juperrin         ###   ########.fr       */
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
	if (status >= 128)
	{
		if (SIGQUIT + 128 == status)
			write(1, "Quit", 4);
		write(1, "\n", 1);
	}
	return (status);
}

void	close_redirections(t_shell *shell)
{
	ft_close(&shell->redirects.output_fd);
	ft_close(&shell->redirects.output_cmp_fd);
	ft_close(&shell->redirects.input_fd);
	ft_close(&shell->redirects.input_cmp_fd);
	ft_close(&shell->redirects.heredoc_fd);
	return ;
}

void	destroy_shell(t_shell *shell)
{
	if (NULL == shell)
		return ;
	rl_clear_history();
	free(shell->cur_cmd);
	free(shell->pids.pids);
	close_redirections(shell);
	ft_close(&shell->redirects.stdin_dup);
	ft_close(&shell->redirects.stdout_dup);
	cmds_lst_clear(&shell->cmd_ast);
	dict_clear(&shell->env);
	free(shell);
	return ;
}
