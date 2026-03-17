/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 16:56:51 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/16 18:03:34 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**	get_files(t_status *status)
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
		cur_file = readdir(directory);
	}
	closedir(directory);
}

void	apply_wildcards(t_ast_lst *ast, t_status *status)
{

}
