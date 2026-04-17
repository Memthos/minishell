/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 16:56:51 by mperrine          #+#    #+#             */
/*   Updated: 2026/04/17 11:06:18 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_status	files_to_ast(t_files_lst **files, t_ast_lst *ast)
{
	t_status	status;
	t_ast_lst	*tail;

	status = SUCCESS;
	free(ast->data);
	ast->data = ft_strdup((*files)->data);
	if (!ast->data)
		return (ALLOCATION_FAILURE);
	ast->token = WORD;
	ast->expand_state = DENY;
	ast->right = NULL;
	files_lst_pop(files);
	while (!status && *files)
	{
		tail = ast_lst_last(ast, RIGHT);
		tail->right = ast_lst_new_char((*files)->data, WORD, &status);
		if (status)
			break ;
		ast_lst_last(ast, RIGHT)->expand_state = DENY;
		files_lst_pop(files);
	}
	return (status);
}

static void	update_ast(t_ast_lst *node, t_files_lst **files, t_status *status)
{
	t_ast_lst	*right;

	right = node->right;
	*status = files_to_ast(files, node);
	if (!*status)
		ast_lst_last(node, RIGHT)->right = right;
	else
		ast_lst_clear(&right);
}

static int	file_check(t_string data, t_string model)
{
	if (*model == '\0' && *data == '\0')
		return (0);
	if (*model == '*')
	{
		while (*model == '*')
			model++;
		if (*model == '\0')
			return (0);
		while (*data)
		{
			if (file_check(data, model) == 0)
				return (0);
			data++;
		}
		return (1);
	}
	if (*data == *model)
		return (file_check(data + 1, model + 1));
	return (1);
}

static void	filter_files(t_files_lst **files, t_string model)
{
	t_files_lst	**cur;

	cur = files;
	while (*cur)
	{
		if (!(*cur)->data)
			files_lst_pop(cur);
		else if (file_check((*cur)->data, model))
			files_lst_pop(cur);
		else
			cur = &(*cur)->next;
	}
}

void	apply_wildcards(t_ast_lst *node, t_status *status)
{
	t_files_lst	*files;

	if (*status || !node)
		return ;
	files = NULL;
	if (node->data && node->token == WILDCARD)
	{
		files = get_files(status);
		if (!*status)
		{
			filter_files(&files, node->data);
			if (files)
				update_ast(node, &files, status);
			else
				node->token = WORD;
		}
	}
	if (files)
		files_lst_clear(&files);
	apply_wildcards(node->left, status);
	if (node->token != AND_IF && node->token != OR_IF)
		apply_wildcards(node->right, status);
}
