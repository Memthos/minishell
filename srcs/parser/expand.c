/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 16:37:25 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/23 16:22:34 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_status	expand_to_ast(t_lxr_lst **lxr, t_ast_lst *ast)
{
	t_status	status;
	t_ast_lst	*tmp;

	status = SUCCESS;
	tmp = ast_lst_new(lxr, &status);
	if (status)
		return (status);
	ast->data = ft_strdup(tmp->data);
	if (!ast->data)
		status = ALLOCATION_FAILURE;
	ast->token = WORD;
	ast->expand_state = DENY;
	ast->right = NULL;
	ast_lst_clear(&tmp);
	while (!status && *lxr)
	{
		ast_lst_last(ast, RIGHT)->right = ast_lst_new(lxr, &status);
		if (status)
			break ;
		ast_lst_last(ast, RIGHT)->token = WORD;
		ast_lst_last(ast, RIGHT)->expand_state = DENY;
	}
	return (status);
}

static void	update_ast(t_ast_lst *node, t_status *status)
{
	t_lxr_lst	*lxr;
	t_ast_lst	*right;

	lxr = NULL;
	right = node->right;
	lexer(&lxr, node->data, status);
	if (!*status)
		*status = expand_to_ast(&lxr, node);
	lxr_lst_clear(&lxr);
	if (!*status)
		ast_lst_last(node, RIGHT)->right = right;
	else
		ast_lst_clear(&right);
}

static int	get_var_name(char *s, char **name)
{
	size_t	size;

	size = 0;
	if (ft_isalpha(s[0]) || s[0] == '_')
	{
		while (ft_isalnum(s[size]) || s[size] == '_')
			size++;
	}
	else if (s[0] == '?' || s[0] == '@' || s[0] == '*' || s[0] == '#'
		|| s[0] == '$' || s[0] == '!' || s[0] == '-' || s[0] == '_'
		|| ft_isdigit(s[0]))
		size = 1;
	else
		return (0);
	*name = malloc(sizeof(char) * (size + 1));
	if (!*name)
		return (1);
	ft_strlcpy(*name, s, size + 1);
	return (0);
}

static t_status	update_data(char **data, size_t *data_i, t_dictionary *dict)
{
	size_t	name_len;
	char	*value;
	char	*str;

	str = NULL;
	if (get_var_name(*data + *data_i + 1, &str))
		return (ALLOCATION_FAILURE);
	if (!str)
	{
		(*data_i)++;
		return (SUCCESS);
	}
	name_len = ft_strlen(str);
	value = dict_get_data(dict, str);
	free(str);
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

void	expand(t_ast_lst *node, t_status *status, t_dictionary *dict)
{
	size_t		i;
	size_t		quotes_rmv;

	if (*status || !node)
		return ;
	i = 0;
	quotes_rmv = 0;
	if (can_expand(node) && get_quotes_rmv(node, &quotes_rmv))
	{
		while (!*status && node->data[i])
		{
			if (node->data[i] == '$' && node->data[i + 1])
			{
				*status = update_data(&node->data, &i, dict);
				if (!*status)
					update_ast(node, status);
			}
			else
				i++;
		}
		if (quotes_rmv > 0 && quotes_rmv % 2 == 0)
			*status = remove_quotes(node, quotes_rmv);
	}
	expand(node->left, status, dict);
	expand(node->right, status, dict);
}
