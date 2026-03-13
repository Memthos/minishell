/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 16:37:25 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/13 19:07:03 by mperrine         ###   ########.fr       */
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
		return (1);
	*var = malloc(sizeof(char) * (size + 1));
	if (!*var)
		return (1);
	ft_strlcpy(*var, &s[i], size + 1);
	return (0);
}

static int	update_data(char **data, size_t *data_i)
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
	var_val = getenv(var_name);
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

static t_ast_lst	*expand_to_ast(t_lxr_lst **lxr, int *ret)
{
	t_ast_lst	*ast;
	t_ast_lst	*tail;

	ast = NULL;
	while (ret && *lxr)
	{
		if (ast)
		{
			tail->right = ast_lst_new(lxr, &ret, WORD);
			tail = tail->right;
		}
		else
		{
			ast = ast_lst_new(lxr, &ret, WORD);
			tail = ast;
		}
		if (!ret)
			break ;
		consume(lxr);
	}
	if (!ret)
		ast_lst_clear(&ast);
	lxr_lst_clear(lxr);
	return (ast);
}

static int	check_expand_data(t_ast_lst *node)
{
	t_ast_lst	*ast;
	t_lxr_lst	*lxr;
	int			ret;

	ret = 1;
	lxr = NULL;
	if (lexer(&lxr, node->data))
		return (1);
	ast = expand_to_ast(&lxr, &ret);
	if (!ret || !ast)
		return (1);
	ast_lst_last(ast, RIGHT)->right = node->right;
	node->right = ast;
	return (0);
}

int	expand(t_ast_lst *node)
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
			if (update_data(&node->data, &i))
				return (1);
			if (check_expand_data(node))
				return (1);
		}
		else
			i++;
	}
	if (expand(node->left) || expand(node->right))
		return (1);
	return (0);
}
