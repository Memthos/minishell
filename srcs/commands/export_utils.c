/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 20:41:18 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/26 19:57:21 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	export_display_env(t_shell *shell)
{
	t_dictionary	*cpy;

	cpy = dict_copy(shell->env);
	if (NULL == cpy)
		return (FAILURE);
	dict_sort(&cpy);
	dict_display(cpy, "declare -x ", "=\"", "\"");
	dict_clear(&cpy);
	return (SUCCESS);
}

t_status	export_special_case(t_strings *args)
{
	if ('=' == ***args || '+' == ***args)
	{
		error_output("export", "not a valid identifier", NO_ERR_MSG);
		++(*args);
		return (FAILURE);
	}
	return (SUCCESS);
}

t_strings	export_set_entry(t_strings *args)
{
	t_strings			entry;

	entry = str_split_at(**args, '=');
	if (NULL == entry)
	{
		perror("malloc");
		++(*args);
		return (NULL);
	}
	return (entry);
}

t_status	export_check_entry(t_strings *entry, t_strings *args, bool *cat)
{
	*cat = false;
	if ((*entry)[0][0] && (*entry)[0][ft_strlen((*entry)[0]) - 1] == '+')
	{
		*cat = true;
		(*entry)[0][ft_strlen((*entry)[0]) - 1] = '\0';
	}
	if (!check_var_name((*entry)[0]))
	{
		error_output("export", "not a valid identifier", NO_ERR_MSG);
		++(*args);
		free((*entry)[0]);
		free((*entry)[1]);
		free((*entry));
		*entry = NULL;
		return (FAILURE);
	}
	return (SUCCESS);
}

t_status	export_update_env(t_strings *entry, t_shell *shell, bool concat)
{
	const t_dictionary	*cpy = dict_get(shell->env, (*entry)[0]);
	t_string			tmp;

	tmp = (*entry)[1];
	if (concat && cpy)
	{
		tmp = ft_strjoin((const t_string)cpy->data, (*entry)[1]);
		free((*entry)[1]);
		if (NULL == tmp)
		{
			perror("malloc");
			free((*entry)[0]);
			free(*entry);
			return (FAILURE);
		}
	}
	if (NULL == tmp && NULL != cpy)
		strings_free(*entry);
	else
	{
		if (!dict_add(&shell->env, (*entry)[0], tmp))
			perror("malloc");
		free(*entry);
	}
	return (SUCCESS);
}
