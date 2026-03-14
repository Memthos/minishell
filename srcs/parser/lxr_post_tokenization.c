/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lxr_post_tokenization.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 22:31:18 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/14 18:04:38 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static void	set_io_number(t_lxr_lst *lxr)
{
	size_t	i;

	if (!lxr->data)
		return ;
	i = 0;
	while (lxr->data[i] && lxr->data[i] >= '0' && lxr->data[i] <= '9')
		i++;
	if (i == ft_strlen(lxr->data) && lxr->next
		&& (lxr->next->token > 4 && lxr->next->token < 9))
		lxr->token = IO_NUMBER;
}

void	set_final_tokens(t_lxr_lst *lxr)
{
	while (lxr)
	{
		set_wildcard(lxr);
		set_io_number(lxr);
		lxr = lxr->next;
	}
}
