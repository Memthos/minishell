/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lxr_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 17:01:37 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/14 18:06:01 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	parenthesis_check(t_lxr_lst *lxr)
{
	if (lxr->token == L_PAREN || lxr->token == AND_IF
		|| lxr->token == OR_IF || lxr->token == PIPE)
	{
		if (!lxr->next || lxr->next->token == END_OF_INPUT
			|| lxr->next->token == R_PAREN || lxr->next->token == AND_IF
			|| lxr->next->token == OR_IF || lxr->next->token == PIPE)
			return (PARENTHESIS_FAILURE);
	}
	else if (lxr->token == R_PAREN)
	{
		if (lxr->next && (lxr->next->token == WORD
				|| lxr->next->token == WILDCARD
				|| lxr->next->token == L_PAREN))
			return (PARENTHESIS_FAILURE);
	}
	else if ((lxr->token == WORD || lxr->token == WILDCARD) && lxr->next
		&& lxr->next->token == L_PAREN)
		return (PARENTHESIS_FAILURE);
	return (SUCCESS);
}

static int	quote_check(t_lxr_lst *lxr)
{
	size_t		i;
	t_quote_t	quote_state;

	if (!lxr->data)
		return (SUCCESS);
	i = 0;
	quote_state = 0;
	while (lxr->data[i])
	{
		set_quote_state(&quote_state, lxr->data[i]);
		i++;
	}
	if (quote_state != 0)
		return (QUOTES_FAILURE);
	return (SUCCESS);
}

void	checker_lxr(t_lxr_lst *lxr, t_status *status)
{
	if (!lxr)
		return ;
	if (lxr->token == AND_IF || lxr->token == OR_IF || lxr->token == PIPE)
		return (FAILURE);
	while (!*status && lxr->token != END_OF_INPUT)
	{
		if (lxr->p_dpt < 0 || parenthesis_check(lxr))
			*status = PARENTHESIS_FAILURE;
		if (quote_check(lxr))
			*status = QUOTES_FAILURE;
		lxr = lxr->next;
	}
	if (lxr->p_dpt != 0)
		*status = PARENTHESIS_FAILURE;
}
