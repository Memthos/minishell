/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lxr_lst_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 11:09:00 by juperrin          #+#    #+#             */
/*   Updated: 2026/01/28 23:09:31 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_lxr_lst	*lxr_lst_new(char *data, t_token token, size_t p_dpt, int quote)
{
	t_lxr_lst	*new;

	new = (t_lxr_lst *)malloc(sizeof(t_lxr_lst));
	if (NULL == new)
		return (NULL);
	new->data = data;
	new->token = token;
	new->p_dpt = p_dpt;
	new->quote = quote;
	new->next = NULL;
	return (new);
}
