/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 16:37:25 by mperrine          #+#    #+#             */
/*   Updated: 2026/04/07 15:56:55 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	update_ast(t_ast_lst *node, t_status *status)
{
	t_lxr_lst	*lxr;
	t_ast_lst	*right;

	if (*status)
		return ;
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

static int	update_node_data(char **data, size_t name_len, char *val, size_t *i)
{
	char	*res;

	if ((*data)[0] == '~')
		res = calloc(ft_strlen(*data) + ft_strlen(val), 1);
	else
		res = calloc(ft_strlen(*data) - name_len + ft_strlen(val), 1);
	if (!res)
		return (ALLOCATION_FAILURE);
	ft_strlcpy(res, *data, *i + 1);
	ft_strlcat(res, val, ft_strlen(res) + ft_strlen(val) + 1);
	if ((*data)[0] == '~')
		ft_strlcat(res, *data + *i + 1, ft_strlen(res)
			+ ft_strlen(*data + *i + 1) + 1);
	else
		ft_strlcat(res, *data + *i + 1 + name_len, ft_strlen(res)
			+ ft_strlen(*data + *i + 1 + name_len) + 1);
	*i += ft_strlen(val);
	free(*data);
	*data = res;
	return (SUCCESS);
}

t_status	expand_node(char **data, size_t *i, t_shell *shell, int is_red)
{
	t_status	status;
	size_t		name_len;
	char		*var_value;
	char		*var_name;

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
		amb_red_error_print(*data);
		return (FAILURE);
	}
	status = update_node_data(data, name_len, var_value, i);
	if (var_value)
		free(var_value);
	return (status);
}

static void	expand_loop(t_ast_lst **node, t_status *status, t_shell *shell,
	int is_red)
{
	size_t	i;

	i = 0;
	while (!*status && (*node)->data && (*node)->data[i])
	{
		if (((*node)->data[i] == '$' && (*node)->data[i + 1])
			|| (i == 0 && (*node)->data[i] == '~'))
		{
			*status = expand_node(&(*node)->data, &i, shell, is_red);
			update_ast(*node, status);
		}
		else
			i++;
	}
}

void	expand(t_ast_lst **node, t_status *status, t_shell *shell, int is_red)
{
	size_t		quotes_rmv;

	if (*status || !node || !*node)
		return ;
	quotes_rmv = 0;
	if (can_expand(*node, status, shell) && get_quotes_rmv(*node, &quotes_rmv))
	{
		expand_loop(node, status, shell, is_red);
		if (ft_strlen((*node)->data) == 0)
		{
			ast_lst_pop(node);
			if (!node || !*node)
				return (1);
		}
		if (!*status && quotes_rmv > 0 && quotes_rmv % 2 == 0)
			*status = remove_quotes(*node, quotes_rmv);
	}
	expand(&(*node)->left, status, shell, is_redirection(*node));
	if ((*node)->token != AND_IF && (*node)->token != OR_IF)
		expand(&(*node)->right, status, shell, is_redirection(*node));
}
