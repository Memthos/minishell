/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 16:56:51 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/17 18:39:43 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	apply_wildcards(t_ast_lst *node, t_status *status)
{
	t_files_lst	*files;

	if (*status || !node)
		return ;
	if (node->data && node->token == WILDCARD)
	{
		files = get_files(status);
		if (!*status)
			filter_files(files, node->data);
	}
	apply_wildcards(node->left, status);
	apply_wildcards(node->right, status);
}
