/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 21:13:55 by mperrine          #+#    #+#             */
/*   Updated: 2026/04/06 21:14:51 by mperrine         ###   ########.fr       */
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

int	ft_close(int *fd)
{
	int	code;

	if (*fd < 0)
		return (SUCCESS);
	code = close(*fd);
	if (SUCCESS != code)
		perror("close");
	*fd = -1;
	return (code);
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

void	*increment_array(void *array, t_uint count, t_uint size)
{
	void	*new;

	if (NULL == array)
	{
		array = ft_calloc(1, size);
		if (NULL == array)
			return (NULL);
		return (array);
	}
	if (0 == count)
		return (array);
	new = ft_calloc(count + 1, size);
	if (NULL == new)
		return (NULL);
	ft_memcpy(new, array, count * size);
	free(array);
	return (new);
}
