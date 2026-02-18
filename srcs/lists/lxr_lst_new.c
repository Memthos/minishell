/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lxr_lst_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:52:35 by mperrine          #+#    #+#             */
/*   Updated: 2026/02/17 14:52:37 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_lxr_lst	*lxr_lst_new(char *data, t_token token, long p_dpt)
{
	t_lxr_lst	*new;

	new = (t_lxr_lst *)malloc(sizeof(t_lxr_lst));
	if (NULL == new)
		return (NULL);
	new->data = data;
	new->token = token;
	new->p_dpt = p_dpt;
	new->next = NULL;
	return (new);
}
