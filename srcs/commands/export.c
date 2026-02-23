/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 13:17:30 by juperrin          #+#    #+#             */
/*   Updated: 2026/02/23 10:15:04 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_status	cmd_export(char **args, t_dictionary **env_dict)
{
	t_status		code;
	t_dictionary	*cpy;
	bool			concat;
	char			**entry;
	char			*tmp;

	if (NULL == env_dict || NULL == *env_dict)
		return (FAILURE);
	if (NULL == args || NULL == *args)
	{
		cpy = *env_dict;
		dict_sort(&cpy);
		dict_display(cpy, "delcare -x ", "=");
		return (SUCCESS);
	}
	code = SUCCESS;
	while (*args)
	{
		concat = false;
		entry = split_at(*args, '=');
		if (NULL == entry)
		{
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
		if (NULL == dict_add(env_dict, entry[0], entry[1]))
		{
			if (!concat)
			{
				dict_update(*env_dict, entry[0], entry[1]);
				free(entry[0]);
			}
			else
			{
				cpy = dict_get(*env_dict, entry[0]);
				tmp = ft_strjoin((const char *)cpy->data, entry[1]);
				dict_update(*env_dict, entry[0], tmp);
				free(entry[0]);
				free(entry[1]);
			}
		}
		free(entry);
		++args;
	}
	return (code);
}
