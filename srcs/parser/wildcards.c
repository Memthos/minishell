/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 16:56:51 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/17 19:10:39 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_status	files_to_ast(t_files_lst *files, t_ast_lst *ast)
{
	t_status	status;
	t_ast_lst	*tail;

	status = SUCCESS;
	free(ast->data);
	ast->data = ft_strdup(files->data);
	if (!ast->data)
		status = ALLOCATION_FAILURE;
	ast->token = WORD;
	ast->right = NULL;
	while (!status && files)
	{
		tail = ast_lst_last(ast, RIGHT);
		tail->right = ast_lst_new_char(files->data, WORD, &status);
		if (status)
			break ;
		files_lst_pop(files);
	}
	return (status);
}

static void	update_ast(t_ast_lst *node, t_files_lst *files, t_status *status)
{
	t_ast_lst	*right;

	right = node->right;
	*status = files_to_ast(files, node);
	if (!*status)
		ast_lst_last(node, RIGHT)->right = right;
	else
		ast_lst_clear(&right);
}

static void	filter_files(t_files_lst *files, char *model)
{
	size_t	i;
	size_t	j;

	while (files)
	{
		i = 0;
		while (model[i] && files->data[j])
		{
			if (model[i] == files->data[j])
			{
				i++;
				j++;
			}
			else if (model[i] == '*')
			{
				i++;
				while (files->data[j] && model[i] != files->data[j])
					j++;
			}
			if (model[i] != files->data[j])
				files_lst_pop(files);
		}
		if (files)
			files = files->next;
	}
}

static t_files_lst	*get_files(t_status *status)
{
	DIR				*directory;
	struct dirent	*cur_file;
	t_files_lst		*files;


	directory =  opendir(".");
	if (!directory)
	{
		*status = WILDCARD_FAILURE;
		return (NULL);
	}
	cur_file = readdir(directory);
	while (cur_file)
	{
		if (files_lst_add(cur_file->d_name, &files, status))
			break ;
		cur_file = readdir(directory);
	}
	closedir(directory);
	if (*status)
		files_lst_clear(&files);
	return (files);
}

void	apply_wildcards(t_ast_lst *node, t_status *status)
{
	t_files_lst	*files;

	if (*status || !node)
		return ;
	if (node->data && node->token == WILDCARD)
	{
		files = get_files(status);
		if (!*status)
		{
			filter_files(files, node->data);
			if (files)
				update_ast(node, files, status);
		}
	}
	apply_wildcards(node->left, status);
	apply_wildcards(node->right, status);
}
