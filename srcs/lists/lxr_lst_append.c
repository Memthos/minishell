/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lxr_lst_append.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 10:08:08 by mperrine          #+#    #+#             */
/*   Updated: 2026/04/23 01:46:26 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	lxr_lst_append(t_lxr_lst **head, char c)
{
	t_string	clean_char;
	t_string	new_str;
	t_lxr_lst	*tmp;

	if (NULL == head)
		return (FAILURE);
	clean_char = make_str(&c, 1);
	if (!clean_char)
		return (ALLOCATION_FAILURE);
	tmp = lxr_lst_last(*head);
	if (!tmp->data)
		tmp->data = clean_char;
	else
	{
		new_str = ft_strjoin(tmp->data, clean_char);
		free(clean_char);
		if (!new_str)
			return (ALLOCATION_FAILURE);
		free(tmp->data);
		tmp->data = new_str;
	}
	return (SUCCESS);
}
