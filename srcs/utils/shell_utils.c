/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 21:13:55 by mperrine          #+#    #+#             */
/*   Updated: 2026/04/07 09:52:29 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_dictionary	*update_shlvl(t_dictionary **env)
{
	t_dictionary	*shlvl;
	int				lvl;

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

bool	check_path(t_shell *shell)
{
	t_dictionary	*e;

	if (NULL == shell || NULL == shell->env)
		return (false);
	e = dict_get(shell->env, "PATH");
	if (NULL == e)
		return (false);
	if (*((char *)e->data) == '\0')
		return (false);
	return (true);
}

bool	check_var_name(char *name)
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
