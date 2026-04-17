/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 09:41:21 by mperrine          #+#    #+#             */
/*   Updated: 2026/04/17 11:35:46 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static DIR	*open_dir(t_status *status)
{
	DIR	*directory;

	directory = opendir(".");
	if (!directory)
	{
		*status = FAILURE;
		error_output(NULL, NULL, READDIR_FAILURE);
		return (NULL);
	}
	return (directory);
}

t_files_lst	*get_files(t_status *status)
{
	DIR				*directory;
	struct dirent	*cur_file;
	t_files_lst		*files;

	files = NULL;
	directory = open_dir(status);
	if (*status)
		return (NULL);
	cur_file = readdir(directory);
	while (cur_file)
	{
		if (ft_strcmp(cur_file->d_name, ".") != 0
			&& ft_strcmp(cur_file->d_name, "..") != 0)
			files_lst_add(cur_file->d_name, &files, status);
		if (*status)
			break ;
		cur_file = readdir(directory);
	}
	closedir(directory);
	if (*status)
		files_lst_clear(&files);
	return (files);
}
