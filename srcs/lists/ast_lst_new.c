/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_lst_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 11:09:00 by juperrin          #+#    #+#             */
/*   Updated: 2026/01/28 23:09:31 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast_lst	*ast_lst_new(t_lxr_lst **lxr)
{
	t_ast_lst	*new;
	char		*str;

	new = (t_ast_lst *)malloc(sizeof(t_ast_lst));
	if (NULL == new)
		return (NULL); //ADD FREE
	str = ft_strcpy((*lxr)->data);
	if (!str)
		return (NULL); //ADD FREE
	new->data = str;
	new->token = (*lxr)->token;
	new->p_dpt = (*lxr)->p_dpt;
	new->left = NULL;
	new->right = NULL;
	consume(lxr);
	return (new);
}
