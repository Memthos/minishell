/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 16:37:25 by mperrine          #+#    #+#             */
/*   Updated: 2026/02/22 15:25:36 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_var_name(char *s, size_t i, char **var)
{
	size_t	size;

	size = 0;
	if (s[i + size] && s[i + size] == '?')
		size++;
	else
	{
		if (!ft_isalpha(s[i]) && s[i] != '_')
			return (0);
		while (s[i + size] && (ft_isalnum(s[i + size]) || s[i + size] == '_'))
			size++;
	}
	if (size == 0)
		return (0);
	*var = malloc(sizeof(char) * (size + 1));
	if (!*var)
		return (1);
	ft_strlcpy(*var, &s[i], size + 1);
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
		value = env[i] + ft_strlen(var) + 1;
	}
	return (value);
}

static int	update_data(char **data, size_t *data_i, char **env)
{
	char	*var_name;
	char	*var_val;
	char	*str;

	var_name = NULL;
	if (get_var_name(*data, *data_i + 1, &var_name))
		return (1);
	if (!var_name)
	{
		(*data_i)++;
		return (0);
	}
	var_val = get_var_value(var_name, env);
	str = malloc(ft_strlen(*data) - ft_strlen(var_name) + ft_strlen(var_val));
	if (!str)
		return (1);
	str[0] = '\0';
	ft_strlcat(str, *data, *data_i);
	ft_strlcat(str, var_val, ft_strlen(var_val) + 1);
	*data_i += ft_strlen(var_name) + 1;
	ft_strlcat(str, *data + *data_i, ft_strlen(*data + *data_i) + 1);
	return (0);
}

int	expand(t_ast_lst *node, char **env)
{
	size_t	i;

	if (node->token != WORD || !node->data)
		return (0);
	i = 0;
	while (node->data[i])
	{
		if (node->data[i] == '$' && update_data(&node->data, &i, env))
			return (1);
		else
			i++;
	}
	return (0);
}
