/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 16:56:51 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/17 11:18:48 by mperrine         ###   ########.fr       */
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
		return ;
	}
	cur_file = readdir(directory);
	while (cur_file)
	{
		if (files_lst_add(cur_file, &files, status))
			break ;
		cur_file = readdir(directory);
	}
	closedir(directory);
	if (*status)

	return (files);
}

void	apply_wildcards(t_ast_lst *ast, t_status *status)
{
	t_files_lst	*files;

	files = get_files(status);
}
