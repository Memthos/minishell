/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 16:37:25 by mperrine          #+#    #+#             */
/*   Updated: 2026/02/23 14:57:13 by mperrine         ###   ########.fr       */
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

static char	*get_var_value(char *var, t_dictionary *env)
{
	char	*value;

	value = getenv(var);
	if (!value)
	{
		while (env && strcmp(env->key, var))
			env = env->next;
		if (!env)
			return (NULL);
		value = env->data;
	}
	return (value);
}

static int	update_data(char **data, size_t *data_i, t_dictionary *env)
{
	size_t	var_name_s;
	char	*var_name;
	char	*var_val;
	char	*str;

	var_name = NULL;
	if (get_var_name(*data, *data_i + 1, &var_name))
		return (1);
	if (!var_name)
		return (0);
	var_name_s = ft_strlen(var_name);
	var_val = get_var_value(var_name, env);
	free(var_name);
	str = malloc(ft_strlen(*data) - var_name_s + ft_strlen(var_val));
	if (!str)
		return (1);
	ft_strlcpy(str, *data, *data_i + 1);
	ft_strlcat(str, var_val, ft_strlen(str) + ft_strlen(var_val) + 1);
	ft_strlcat(str, *data + *data_i + 1 + var_name_s, ft_strlen(str)
		+ ft_strlen(*data + *data_i + 1 + var_name_s) + 1);
	if (var_val)
		*data_i += ft_strlen(var_val) - 1;
	free(*data);
	*data = str;
	return (0);
}

int	expand(t_ast_lst *node, t_dictionary *env)
{
	size_t		i;
	t_quote_t	quote_state;

	if (!node || !node->data
		|| (node->token != WORD && node->token != WILDCARD))
		return (0);
	i = 0;
	quote_state = 0;
	while (node->data[i])
	{
		set_quote_state(&quote_state, node->data[i]);
		if (node->data[i] == '$' && quote_state != 1)
		{
			if (update_data(&node->data, &i, env))
				return (1);
		}
		else
			i++;
	}
	if (expand(node->left, env))
		return (1);
	if (expand(node->right, env))
		return (1);
	return (0);
}
