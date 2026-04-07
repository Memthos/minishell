/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 13:17:30 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/07 15:15:29 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_status	cmd_export(char **args, t_shell *shell)
{
	bool			concat;
	char			**entry;
	char			*tmp;
	t_status		code;
	t_dictionary	*cpy;

	if (NULL == shell)
		return (FAILURE);
	if (NULL == args[1])
	{
		cpy = dict_copy(shell->env);
		dict_sort(&cpy);
		dict_display(cpy, "declare -x ", "=\"", "\"");
		dict_clear(&cpy);
		return (SUCCESS);
	}
	code = SUCCESS;
	++args;
	while (*args)
	{
		concat = false;
		if ('=' == **args)
		{
			error_output("export", "not a valid identifier", NO_ERR_MSG);
			code = FAILURE;
			++args;
			continue ;
		}
		entry = split_at(*args, '=');
		if (NULL == entry)
		{
			if (!check_var_name(*args))
			{
				error_output("export", "not a valid identifier", NO_ERR_MSG);
				code = FAILURE;
				++args;
				continue ;
			}
			if (NULL == dict_add(&shell->env, ft_strdup(*args), NULL))
				perror("malloc");
			++args;
			continue ;
		}
		if (entry[0][ft_strlen(entry[0]) - 1] == '+')
		{
			concat = true;
			entry[0][ft_strlen(entry[0]) - 1] = '\0';
		}
		if (!check_var_name(entry[0]))
		{
			error_output("export", "not a valid identifier", NO_ERR_MSG);
			++args;
			free(entry[0]);
			free(entry[1]);
			free(entry);
			code = FAILURE;
			continue ;
		}
		if (concat)
		{
			cpy = dict_get(shell->env, entry[0]);
			tmp = ft_strjoin((const char *)cpy->data, entry[1]);
			if (NULL == dict_add(&shell->env, entry[0], tmp))
				perror("malloc");
			free(entry[1]);
		}
		else
			if (NULL == dict_add(&shell->env, entry[0], entry[1]))
				perror("malloc");
		free(entry);
		++args;
	}
	return (code);
}
