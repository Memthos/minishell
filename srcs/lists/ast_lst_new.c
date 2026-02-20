/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_lst_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 10:08:18 by mperrine          #+#    #+#             */
/*   Updated: 2026/02/20 20:53:38 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast_lst	*ast_lst_new(t_lxr_lst **lxr, int *ret)
{
	t_ast_lst	*new;
	char		*str;

	new = malloc(sizeof(t_ast_lst));
	if (NULL == new)
	{
		*ret = 0;
		return (NULL);
	}
	if (!(*lxr)->data)
		str = NULL;
	else
	{
		str = ft_strdup((*lxr)->data);
		if (!str)
		{
			free(new);
			*ret = 0;
			return (NULL);
		}
	}
	*new = (t_ast_lst){.data = str, .token = (*lxr)->token,
		.p_dpt = (*lxr)->p_dpt, .left = NULL, .right = NULL};
	consume(lxr);
	return (new);
}
