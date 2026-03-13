/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 02:21:00 by juperrin          #+#    #+#             */
/*   Updated: 2026/03/13 14:25:10 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	set_shell(t_shell *shell)
{
	if (NULL == shell)
		return ;
	shell->cmd_ast = NULL;
	shell->locals = NULL;
	shell->cur_cmd = NULL;
	shell->exitno = SUCCESS;
	shell->pipes.redirect_output = false;
	shell->pipes.redirect_input = false;
	shell->pipes.pipe1[0] = -1;
	shell->pipes.pipe1[1] = -1;
	shell->pipes.pipe2[0] = -1;
	shell->pipes.pipe2[1] = -1;
	shell->pipes.pipe_index = 0;
	shell->pipes.pipe_depth = 0;
	shell->pids.pids = NULL;
	shell->pids.pid_count = 0;
	shell->pids.pid_index = 0;
	return ;
}

t_shell	*init(char *envp[])
{
	t_shell	*shell;

	shell = (t_shell *)malloc(sizeof(t_shell));
	if (NULL == shell)
		return (NULL);
	if (SUCCESS != init_signals())
	{
		free(shell);
		return (NULL);
	}
	shell->env = init_env(envp);
	if (NULL == shell->env)
	{
		free(shell);
		return (NULL);
	}
	set_shell(shell);
	return (shell);
}
