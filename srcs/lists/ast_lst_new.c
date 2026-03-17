/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_lst_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 10:08:18 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/17 18:59:02 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast_lst	*ast_lst_new_char(char *data, t_token token, t_status *status)
{
	t_ast_lst	*new;
	char		*str;

	new = malloc(sizeof(t_ast_lst));
	if (NULL == new)
	{
		*status = ALLOCATION_FAILURE;
		return (NULL);
	}
	str = ft_strdup(data);
	if (!str)
	{
		free(new);
		*status = ALLOCATION_FAILURE;
		return (NULL);
	}
	*new = (t_ast_lst){str, token, 0, NULL, NULL};
	return (new);
}

t_ast_lst	*ast_lst_new(t_lxr_lst **lxr, t_status *status)
{
	t_ast_lst	*new;
	char		*str;

	new = malloc(sizeof(t_ast_lst));
	if (NULL == new)
	{
		*status = ALLOCATION_FAILURE;
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
			*status = ALLOCATION_FAILURE;
			return (NULL);
		}
	}
	*new = (t_ast_lst){str, (*lxr)->token, 0, NULL, NULL};
	consume(lxr);
	return (new);
}
