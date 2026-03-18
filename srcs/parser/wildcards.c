/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 16:56:51 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/18 15:12:56 by mperrine         ###   ########.fr       */
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

static int	file_check(t_files_lst **cur, char *model)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	while (model[i] || (*cur)->data[j])
	{
		while (model[i] && (*cur)->data[j] && model[i] == (*cur)->data[j])
		{
			i++;
			j++;
		}
		if (model[i] == '*')
		{
			i++;
			while ((*cur)->data[j] && (*cur)->data[j] != next_char(model, i))
				j++;
		}
		if (model[i] != (*cur)->data[j] && model[i] != '*')
			return (1);
		else if (model[i] == '\0' && (*cur)->data[j] == '\0')
			return (0);
	}
	return (1);
}

static void	filter_files(t_files_lst **files, char *model)
{
	t_files_lst	**cur;

	cur = files;
	while (*cur)
	{
		if (file_check(cur, model))
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
	apply_wildcards(node->right, status);
}
