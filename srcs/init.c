/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 02:21:00 by juperrin          #+#    #+#             */
/*   Updated: 2026/02/23 15:50:08 by juperrin         ###   ########.fr       */
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
	init_commands(shell);
	shell->cmd_ast = NULL;
	return (shell);
}
