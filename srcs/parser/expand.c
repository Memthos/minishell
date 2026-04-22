/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 16:37:25 by mperrine          #+#    #+#             */
/*   Updated: 2026/04/23 01:46:35 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_ast(t_ast_lst *node, t_status *status)
{
	t_lxr_lst	*lxr;
	t_ast_lst	*right;

	lxr = NULL;
	right = node->right;
	lexer(&lxr, node->data, status);
	if (!*status)
	{
		if (!lxr)
		{
			node->data = calloc(1, 1);
			if (!node->data)
				*status = ALLOCATION_FAILURE;
			return ;
		}
		else
			*status = expand_to_ast(&lxr, node);
	}
	lxr_lst_clear(&lxr);
	if (!*status)
		ast_lst_last(node, RIGHT)->right = right;
	else
		ast_lst_clear(&right);
}

static int	update_node_data(t_strings data, size_t n, t_string val, size_t *i)
{
	t_string	res;

	if ((*data)[0] == '~')
		res = calloc(ft_strlen(*data) + ft_strlen(val), 1);
	else
		res = calloc(ft_strlen(*data) - n + ft_strlen(val), 1);
	if (!res)
		return (ALLOCATION_FAILURE);
	ft_strlcpy(res, *data, *i + 1);
	ft_strlcat(res, val, ft_strlen(res) + ft_strlen(val) + 1);
	if ((*data)[0] == '~')
		ft_strlcat(res, *data + *i + 1, ft_strlen(res)
			+ ft_strlen(*data + *i + 1) + 1);
	else
		ft_strlcat(res, *data + *i + 1 + n, ft_strlen(res)
			+ ft_strlen(*data + *i + 1 + n) + 1);
	*i += ft_strlen(val);
	free(*data);
	*data = res;
	return (SUCCESS);
}

t_status	expand_node(t_strings data, size_t *i, t_shell *shell, int is_red)
{
	t_status	status;
	size_t		name_len;
	t_string	var_value;
	t_string	var_name;

	status = SUCCESS;
	var_name = NULL;
	if (get_var_name(*data + *i, &var_name, i))
		return (ALLOCATION_FAILURE);
	name_len = ft_strlen(var_name);
	var_value = get_expand_value(var_name, shell, &status);
	free(var_name);
	if (status)
		return (ALLOCATION_FAILURE);
	if (is_red && (!var_value || contain_space(var_value)))
	{
		if (var_value)
			free(var_value);
		return (FAILURE);
	}
	status = update_node_data(data, name_len, var_value, i);
	if (var_value)
		free(var_value);
	return (status);
}

static int	expand_loop(t_ast_lst **node, t_status *status, t_shell *shell,
	int is_red)
{
	size_t		i;
	int			did_expand;
	t_quote_t	quote_state;

	i = 0;
	did_expand = 0;
	quote_state = NONE;
	while (!*status && (*node)->data && (*node)->data[i])
	{
		set_quote_state(&quote_state, (*node)->data[i]);
		if (((*node)->data[i] == '$' && (*node)->data[i + 1]
				&& quote_state != S_QUOTE) || (i == 0 && (*node)->data[i] == '~'
				&& (*node)->data[i + 1] == '\0' && quote_state == NONE))
		{
			did_expand = 1;
			*status = expand_node(&(*node)->data, &i, shell, is_red);
			if (*status == FAILURE)
				(*node)->token = AMB_RED;
			else if (!*status)
				update_ast(*node, status);
		}
		else
			i++;
	}
	return (did_expand);
}

void	expand(t_ast_lst **node, t_status *status, t_shell *shell, int is_red)
{
	size_t		quotes_rmv;

	if (*status || !node || !*node)
		return ;
	if (can_expand(*node, status, shell))
	{
		quotes_rmv = get_quotes_rmv(*node);
		if (!expand_loop(node, status, shell, is_red))
			quotes_rmv = 0;
		if (ft_strlen((*node)->data) == 0)
		{
			ast_lst_pop(node);
			if (!node || !*node)
				return ;
		}
		if (!*status && quotes_rmv > 0 && quotes_rmv % 2 == 0)
			*status = remove_quotes(*node, quotes_rmv);
	}
	expand(&(*node)->left, status, shell, is_redirection(*node));
	if ((*node)->token != AND_IF && (*node)->token != OR_IF)
		expand(&(*node)->right, status, shell, is_redirection(*node));
}
