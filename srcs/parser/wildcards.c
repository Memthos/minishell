/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 16:56:51 by mperrine          #+#    #+#             */
/*   Updated: 2026/04/26 16:00:10 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_status	files_to_ast(t_char_lst **files, t_ast_lst *ast)
{
	t_status	status;
	t_ast_lst	*tail;
	t_char_lst	**first;

	first = char_lst_first(files);
	status = SUCCESS;
	free(ast->data);
	ast->data = ft_strdup((*first)->data);
	if (!ast->data)
		return (ALLOCATION_FAILURE);
	ast->token = WORD;
	ast->expand_state = DENY;
	ast->right = NULL;
	char_lst_pop(first);
	while (!status && *files)
	{
		first = char_lst_first(files);
		tail = ast_lst_last(ast, RIGHT);
		tail->right = ast_lst_new_char((*first)->data, WORD, &status);
		if (status)
			break ;
		ast_lst_last(ast, RIGHT)->expand_state = DENY;
		char_lst_pop(first);
	}
	return (status);
}

static void	update_ast(t_ast_lst *node, t_char_lst **files, t_status *status)
{
	t_ast_lst	*right;

	if (*status)
		return ;
	right = node->right;
	*status = files_to_ast(files, node);
	if (!*status)
		ast_lst_last(node, RIGHT)->right = right;
	else
		ast_lst_clear(&right);
}

static void	apply_wildcard(t_ast_lst *node, t_status *status, int is_red)
{
	t_char_lst	*files;

	files = NULL;
	if (!is_red || (is_red && ft_strcmp(node->data, "*") != 0))
	{
		files = get_files(status, node->data);
		if (!*status && files)
		{
			filter_files(&files, node->data);
			if (files)
				update_ast(node, &files, status);
		}
	}
	else if (is_red)
		node->token = AMB_RED;
	if (files)
		char_lst_clear(&files);
}

static int	can_try_wildcard(t_ast_lst *node)
{
	size_t		i;
	t_quote_t	quote_state;

	if (!node->data || node->token != WILDCARD)
		return (0);
	i = 0;
	quote_state = NONE;
	while (node->data[i])
	{
		set_quote_state(&quote_state, node->data[i++]);
		if (node->data[i] == '*' && quote_state != NONE)
			return (0);
	}
	return (1);
}

void	wildcards(t_ast_lst *node, t_status *status, int is_red)
{
	if (*status || !node)
		return ;
	if (can_try_wildcard(node))
		apply_wildcard(node, status, is_red);
	wildcards(node->left, status, is_redirection(node));
	if (node->token != AND_IF && node->token != OR_IF)
		wildcards(node->right, status, is_redirection(node));
}
