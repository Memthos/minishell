/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_lst_add.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 11:06:02 by mperrine          #+#    #+#             */
/*   Updated: 2026/04/17 11:06:18 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	files_lst_add(t_string s, t_files_lst **files, t_status *status)
{
	t_files_lst	*node;

	node = malloc(sizeof(t_files_lst));
	if (!node)
	{
		*status = ALLOCATION_FAILURE;
		return (1);
	}
	node->data = ft_strdup(s);
	if (!node->data)
	{
		*status = ALLOCATION_FAILURE;
		return (1);
	}
	node->next = NULL;
	if (!files || !*files)
		*files = node;
	else
		file_lst_last(*files)->next = node;
	return (0);
}
