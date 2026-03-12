/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 02:21:00 by juperrin          #+#    #+#             */
/*   Updated: 2026/03/12 15:20:15 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	shell->cmd_ast = NULL;
	shell->locals = NULL;
	shell->cur_cmd = NULL;
	shell->exitno = SUCCESS;
	shell->redirect_output = false;
	shell->redirect_input = false;
	shell->pipe1[0] = -1;
	shell->pipe1[1] = -1;
	shell->pipe2[0] = -1;
	shell->pipe2[1] = -1;
	shell->pipe_index = 0;
	shell->pipe_depth = 0;
	shell->pids = NULL;
	shell->pid_count = 0;
	shell->pid_index = 0;
	return (shell);
}
