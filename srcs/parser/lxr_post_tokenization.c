/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lxr_post_tokenization.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 22:31:18 by mperrine          #+#    #+#             */
/*   Updated: 2026/04/17 11:35:46 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_wildcard(t_lxr_lst *lxr)
{
	size_t	i;

	if (!lxr->data)
		return ;
	i = 0;
	while (lxr->data[i])
	{
		if (lxr->data[i] == '*')
			lxr->token = WILDCARD;
		i++;
	}
}

void	set_final_tokens(t_lxr_lst **lxr, t_status *status)
{
	t_lxr_lst	**cpy;

	if (*status || !lxr || !*lxr)
		return ;
	cpy = lxr;
	while (*cpy)
	{
		set_wildcard(*cpy);
		if ((*cpy)->token == TOKEN)
			lxr_lst_pop(cpy);
		else
			cpy = &(*cpy)->next;
	}
}
