/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 16:37:25 by mperrine          #+#    #+#             */
/*   Updated: 2026/04/28 16:57:56 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_node_data(t_strings data, size_t n, t_string val, size_t *i)
{
	t_string	res;

	if ((*data)[0] == '~')
		res = ft_calloc(ft_strlen(*data) + ft_strlen(val), 1);
	else
		res = ft_calloc(ft_strlen(*data) - n + ft_strlen(val) + 1, 1);
	if (!res)
		return (ALLOCATION_FAILURE);
	ft_strlcpy(res, *data, *i + 1);
	ft_strlcat(res, val, ft_strlen(res) + ft_strlen(val) + 1);
	if ((*data)[0] == '~')
		ft_strlcat(res, *data + *i + 1, ft_strlen(res)
			+ ft_strlen(*data + *i + 1) + 1);
	else
		ft_strlcat(res, *data + *i + n, ft_strlen(res)
			+ ft_strlen(*data + *i + n) + 1);
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
	if (get_var_name(*data + *i, &var_name))
		return (ALLOCATION_FAILURE);
	name_len = ft_strlen(var_name) + 1;
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
		if (can_expand((*node)->data, i, quote_state))
		{
			did_expand = 1;
			*status = expand_node(&(*node)->data, &i, shell, is_red);
			if (*status == FAILURE)
				(*node)->token = AMB_RED;
			else if (!*status)
				update_expanded_ast(*node, status);
		}
		else
			i++;
	}
	return (did_expand);
}

static int	try_expand(t_ast_lst **node, t_status *status, t_shell *shell,
	int is_red)
{
	size_t	quotes_rmv;

	quotes_rmv = get_quotes_rmv(*node);
	if (!expand_loop(node, status, shell, is_red))
		quotes_rmv = 0;
	if (ft_strlen((*node)->data) == 0)
	{
		ast_lst_pop(node);
		return (1);
	}
	if (!*status && quotes_rmv > 0 && quotes_rmv % 2 == 0)
		*status = remove_quotes(*node, quotes_rmv);
	return (0);
}

void	expand(t_ast_lst **node, t_status *status, t_shell *shell, int is_red)
{
	int			popped;

	if (*status || !node || !*node)
		return ;
	popped = 0;
	if (can_try_expand(*node, status, shell))
	{
		popped = try_expand(node, status, shell, is_red);
		if (!node || !*node)
			return ;
	}
	expand(&(*node)->left, status, shell, is_redirection(*node));
	if (!popped && (*node)->token != AND_IF && (*node)->token != OR_IF)
		expand(&(*node)->right, status, shell, is_redirection(*node));
	else if (popped && (*node)->token != AND_IF && (*node)->token != OR_IF)
		expand(node, status, shell, 0);
}
