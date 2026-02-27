/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_lst_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 10:08:18 by mperrine          #+#    #+#             */
/*   Updated: 2026/02/25 13:28:59 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast_lst	*ast_lst_new(t_lxr_lst **lxr, int *ret, t_token	force)
{
	t_ast_lst	*new;
	char		*str;

	new = malloc(sizeof(t_ast_lst));
	if (NULL == new)
		*ret = 0;
	if (!*ret)
		return (NULL);
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
		.left = NULL, .right = NULL};
	if (force)
		new->token = force;
	consume(lxr);
	return (new);
}
