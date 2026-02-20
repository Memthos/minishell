/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 13:42:58 by mperrine          #+#    #+#             */
/*   Updated: 2026/02/20 13:43:59 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	set_io_number(t_lxr_lst *lxr)
{
	size_t	i;

	if (!lxr->data)
		return ;
	i = 0;
	while (lxr->data[i] && lxr->data[i] >= '0' && lxr->data[i] <= '9')
		i++;
	if (i == ft_strlen(lxr->data)
		&& (lxr->next->token > 4 || lxr->next->token < 9))
		lxr->token = IO_NUMBER;
}

static void	set_assignment_w(t_lxr_lst *lxr)
{
	size_t	i;

	if (!lxr->data)
		return ;
	i = 0;
	if (!ft_isalpha(lxr->data[i]) && lxr->data[i] != '_')
		return ;
	while (lxr->data[i] && (ft_isalnum(lxr->data[i]) || lxr->data[i] == '_'))
		i++;
	if (lxr->data[i] == '=')
		lxr->token = ASSIGNMENT_W;
}

void	set_final_tokens(t_lxr_lst *lxr)
{
	if (!lxr)
		return ;
	while (lxr)
	{
		set_io_number(lxr);
		set_assignment_w(lxr);
		lxr = lxr->next;
	}
}
