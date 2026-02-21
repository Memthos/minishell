/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 16:37:25 by mperrine          #+#    #+#             */
/*   Updated: 2026/02/21 21:40:36 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_var_name(char *s, char **var)
{
	char	*tmp;
	size_t	i;

	tmp = ft_strchr(s, '$');
	if (!tmp)
		return (0);
	tmp++;
	i = 0;
	while (tmp[i] && (ft_isalnum(tmp[i]) || tmp[i] == '_'))
		i++;
	if (i == 0)
		return (0);
	*var = malloc(sizeof(char) * (i + 1));
	if (!*var)
		return (1);
	ft_strlcpy(*var, tmp, i + 1);
	return (0);
}

static char	*get_var_value(char *var, char **env)
{
	char	*value;
	size_t	i;

	value = getenv(var);
	if (!value)
	{
		i = 0;
		while (env[i] && (strncmp(env[i], var, ft_strlen(var))
			|| env[i][ft_strlen(var)] != '='))
			i++;
		if (!env[i])
			return (NULL);
		value = env[i] + ft_strlen(var);
	}
	return (value);
}

static int	update_data(char **data, char *var, char **env)
{
	char	*value;
	char	*str;
	size_t	i;

	value = get_var_value(var, env);
	if (!value)
		return (0);
	str = malloc(ft_strlen(*data) - ft_strlen(var)+  ft_strlen(value) + 1);
	if (!str)
		return (1);
	i = 0;
	while ((*data)[i] && (*data)[i] != '$')
		i++;
	ft_strlcpy(str, *data, i + 1);
	ft_strlcpy(str + i, value, ft_strlen(value) + 1);
	ft_strlcpy(str + i + ft_strlen(value), *data + i + 1 + ft_strlen(var),
		ft_strlen(*data + i + 1 + ft_strlen(var)) + 1);
	free(*data);
	*data = str;
	return (0);
}

int	expand(t_ast_lst *node, char **env)
{
	char	*var;

	if (node->token != WORD || !node->data)
		return (0);
	while (ft_strchr(node->data, '$'))
	{
		var = NULL;
		if (get_var_name(node->data, &var))
			return (1);
		if (!var)
			return (0);
		if (update_data(&node->data, var, env))
		{
			free(var);
			return (1);
		}
		free(var);
	}
	return (0);
}
