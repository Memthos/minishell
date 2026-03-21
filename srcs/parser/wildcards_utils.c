/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 09:41:21 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/21 14:16:10 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	next_char(char *model, size_t i)
{
	while (model[i] && model[i] == '*')
		i++;
	return (model[i]);
}

t_files_lst	*get_files(t_status *status)
{
	DIR				*directory;
	struct dirent	*cur_file;
	t_files_lst		*files;

	files = NULL;
	directory = opendir(".");
	if (!directory)
	{
		*status = READDIR_FAILURE;
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
