/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 16:37:25 by mperrine          #+#    #+#             */
/*   Updated: 2026/04/07 17:55:00 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_var_name(char *s, char **name, size_t *i)
{
	size_t	size;

	size = 0;
	if (s[0] == '~')
		size = 4;
	else if (ft_isalpha(s[1]) || s[1] == '_')
		while (ft_isalnum(s[size + 1]) || s[size + 1] == '_')
			size++;
	else if (s[1] == '?' || s[1] == '@' || s[1] == '*' || s[1] == '#'
		|| s[1] == '$' || s[1] == '!' || s[1] == '-' || s[1] == '_'
		|| ft_isdigit(s[1]))
		size = 1;
	else
	{
		(*i)++;
		return (0);
	}
	*name = malloc(sizeof(char) * (size + 1));
	if (!*name)
		return (1);
	if (s[0] == '~')
		ft_strlcpy(*name, "HOME", size + 1);
	else
		ft_strlcpy(*name, s + 1, size + 1);
	return (0);
}

char	*get_expand_value(char *var_name, t_shell *shell, t_status *status)
{
	char	*value;
	char	*tmp;

	value = NULL;
	tmp = dict_get_data(shell->env, var_name);
	if (tmp)
	{
		value = ft_strdup(tmp);
		if (!tmp)
		{
			*status = ALLOCATION_FAILURE;
			return (NULL);
		}
	}
	else if (!tmp && ft_strcmp(var_name, "?") == 0)
	{
		value = ft_itoa(shell->oldexitno);
		if (!value)
		{
			*status = ALLOCATION_FAILURE;
			return (NULL);
		}
	}
	return (value);
}
