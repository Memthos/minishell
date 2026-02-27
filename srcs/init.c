/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 02:21:00 by juperrin          #+#    #+#             */
/*   Updated: 2026/02/27 09:29:43 by juperrin         ###   ########.fr       */
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
	shell->stdin_fd = dup(STDIN_FILENO);
	shell->stdout_fd = dup(STDOUT_FILENO);
	return (shell);
}
