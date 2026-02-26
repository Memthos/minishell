/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 10:31:06 by juperrin          #+#    #+#             */
/*   Updated: 2026/02/26 09:42:36 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_dictionary	*init_env(char *envp[])
{
	t_dictionary	*dict;
	char			**tmp;

	dict = NULL;
	while (*envp)
	{
		tmp = split_at(*envp, '=');
		if (NULL == dict_add(&dict, tmp[0], tmp[1]))
		{
			free(tmp);
			dict_clear(&dict);
			return (NULL);
		}
		free(tmp);
		++envp;
	}
	return (dict);
}

t_status	update_locals(t_shell *shell, char *assign)
{
	char	**args;

	if (NULL == shell || NULL == assign)
		return (SUCCESS);
	args = split_at(assign, '=');
	if (NULL == args)
	{
		shell->exitno = ASSIGN_FAILURE;
		return (ASSIGN_FAILURE);
	}
	shell->exitno = SUCCESS;
	if (NULL == dict_add(&shell->locals, args[0], args[1]))
	{
		shell->exitno = ASSIGN_FAILURE;
		free(args[0]);
		free(args[1]);
	}
	free(args);
	return (shell->exitno);	
}
