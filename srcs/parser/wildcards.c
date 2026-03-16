/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 16:56:51 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/16 17:58:49 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	apply_wildcards(t_ast_lst *ast, t_status *status)
{
	(void)ast;
	DIR	*directory;
	struct dirent	*cur_file;

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
		if (cur_file)
			printf("|%s|\n", cur_file->d_name);
	}
	closedir(directory);
}
