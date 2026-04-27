/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 21:13:55 by mperrine          #+#    #+#             */
/*   Updated: 2026/04/26 15:25:13 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dictionary	*update_shlvl(t_dictionary **env)
{
	t_dictionary	*shlvl;
	long			lvl;

	if (NULL == env)
		return (NULL);
	shlvl = dict_get(*env, "SHLVL");
	if (NULL == shlvl || SUCCESS != get_number(shlvl->data, &lvl))
	{
		if (NULL == dict_add(env, ft_strdup("SHLVL"), ft_strdup("0")))
			perror("malloc");
		return (*env);
	}
	free(shlvl->data);
	shlvl->data = ft_itoa(lvl + 1);
	if (NULL == shlvl->data)
		perror("malloc");
	return (*env);
}

bool	check_var_name(t_string name)
{
	if (NULL == name)
		return (false);
	if (!ft_isalpha(*name) && *name != '_')
		return (false);
	while (*name)
	{
		if (!ft_isalnum(*name) && *name != '_')
			return (false);
		++name;
	}
	return (true);
}

bool	is_dir(const t_string path)
{
	struct stat	stat_buf;

	if (SUCCESS != access(path, F_OK) || SUCCESS != stat(path, &stat_buf))
		return (false);
	return (S_ISDIR(stat_buf.st_mode));
}
