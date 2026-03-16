/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 16:37:25 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/16 10:33:29 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_ast_lst	*expand_to_ast(t_lxr_lst **lxr, t_status *status)
{
	t_ast_lst	*ast;

	ast = NULL;
	while (!*status && *lxr)
	{
		if (ast)
			ast_lst_last(ast, RIGHT)->right = ast_lst_new(lxr, status);
		else
			ast = ast_lst_new(lxr, status);
		if (*status)
			break ;
		consume(lxr);
	}
	if (*status)
		ast_lst_clear(&ast);
	return (ast);
}

static void	update_ast(t_ast_lst *node, t_status *status)
{
	t_ast_lst	*ast;
	t_lxr_lst	*lxr;

	lxr = NULL;
	lexer(&lxr, node->data, status);
	if (!*status)
		ast = expand_to_ast(&lxr, status);
	lxr_lst_clear(&lxr);
	if (*status || !ast)
		return ;
	ast_lst_last(ast, RIGHT)->right = node->right;
	node->right = ast;
}

static char	*get_var_name(char *s)
{
	char	*name;
	size_t	size;

	if (s[0] == '?' || ft_isdigit(s[0]))
		size = 1;
	else
		size = ft_strlen(s);
	*name = malloc(sizeof(char) * (size + 1));
	if (!*name)
		return (NULL);
	ft_strlcpy(name, s, size + 1);
	return (name);
}

static t_status	update_data(char **data, size_t *data_i)
{
	size_t	name_len;
	char	*name;
	char	*value;
	char	*str;

	name = get_var_name(*data + *data_i + 1);
	if (!name)
		return (ALLOCATION_FAILURE);
	name_len = ft_strlen(name);
	value = getenv(name);
	free(name);
	str = malloc(ft_strlen(*data) - name_len + ft_strlen(value));
	if (!str)
		return (ALLOCATION_FAILURE);
	ft_strlcpy(str, *data, *data_i + 1);
	ft_strlcat(str, value, ft_strlen(str) + ft_strlen(value) + 1);
	ft_strlcat(str, *data + *data_i + 1 + name_len, ft_strlen(str)
		+ ft_strlen(*data + *data_i + 1 + name_len) + 1);
	free(*data);
	*data = str;
	return (SUCCESS);
}

void	expand(t_ast_lst *node, t_status *status)
{
	size_t		i;
	t_quote_t	quote_state;

	if (*status || !node || !node->data
		|| (node->token != WORD && node->token != WILDCARD))
		return ;
	i = 0;
	quote_state = 0;
	while (node->data[i])
	{
		set_quote_state(&quote_state, node->data[i]);
		if (quote_state != 1 && node->data[i] == '$' && node->data[i + 1])
		{
			*status = update_data(&node->data, &i);
			if (!*status)
				update_ast(node, status);
		}
		else
			i++;
	}
	expand(node->left, status);
	expand(node->right, status);
}
