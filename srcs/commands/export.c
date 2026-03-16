/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 13:17:30 by juperrin          #+#    #+#             */
/*   Updated: 2026/03/16 16:03:20 by juperrin         ###   ########.fr       */
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
		entry = split_at(*args, '=');
		if (NULL == entry)
		{
			if (!ft_isalpha(**args))
			{
				error_output("export : not a valid identifier");
				code = FAILURE;
			}
			++args;
			continue ;
		}
		if (0 == ft_strlen(entry[0]) || 0 == ft_strlen(entry[1]))
		{
			++args;
			free(entry[0]);
			free(entry[1]);
			free(entry);
			continue ;
		}
		if (entry[0][ft_strlen(entry[0]) - 1] == '+')
		{
			concat = true;
			entry[0][ft_strlen(entry[0]) - 1] = '\0';
		}
		if (!check_var_name(entry[0]))
		{
			error_output("export : not a valid identifier");
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
			dict_add(&shell->env, entry[0], tmp);
			free(entry[1]);
		}
		else
			dict_add(&shell->env, entry[0], entry[1]);
		free(entry);
		++args;
	}
	return (code);
}
