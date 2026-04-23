/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 09:41:21 by mperrine          #+#    #+#             */
/*   Updated: 2026/04/23 16:59:02 by mperrine         ###   ########.fr       */
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

t_char_lst	*get_files(t_status *status, char *model)
{
	DIR				*directory;
	struct dirent	*cur_file;
	t_char_lst		*files;

	if (!model)
		return (NULL);
	files = NULL;
	directory = open_dir(status);
	if (*status)
		return (NULL);
	cur_file = readdir(directory);
	while (cur_file)
	{
		if (cur_file->d_name[0] != '.'
			|| (cur_file->d_name[0] == '.' && model[0] == '.'))
			char_lst_add(cur_file->d_name, &files, status);
		if (*status)
			break ;
		cur_file = readdir(directory);
	}
	closedir(directory);
	if (*status)
		char_lst_clear(&files);
	return (files);
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

void	filter_files(t_char_lst **files, t_string model)
{
	t_char_lst	**cur;

	cur = files;
	while (*cur)
	{
		if (!(*cur)->data)
			char_lst_pop(cur);
		else if (file_check((*cur)->data, model))
			char_lst_pop(cur);
		else
			cur = &(*cur)->next;
	}
}
