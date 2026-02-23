/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 12:53:01 by mperrine          #+#    #+#             */
/*   Updated: 2026/02/23 14:52:21 by mperrine         ###   ########.fr       */
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
			return (1);
	}
	else if (lxr->token == R_PAREN)
	{
		if (lxr->next && (lxr->next->token == WORD
				|| lxr->next->token == WILDCARD
				|| lxr->next->token == ASSIGNMENT_W
				|| lxr->next->token == L_PAREN))
			return (1);
	}
	else if ((lxr->token == WORD || lxr->token == ASSIGNMENT_W
			|| lxr->token == WILDCARD) && lxr->next
		&& lxr->next->token == L_PAREN)
		return (1);
	return (0);
}

static int	quote_check(t_lxr_lst *lxr)
{
	size_t		i;
	t_quote_t	quote_state;

	if (!lxr->data)
		return (0);
	i = 0;
	quote_state = 0;
	while (lxr->data[i])
	{
		set_quote_state(&quote_state, lxr->data[i]);
		i++;
	}
	if (quote_state != 0)
		return (1);
	return (0);
}

static int	checker_lxr(t_lxr_lst *lxr)
{
	if (!lxr)
		return (1);
	if (lxr->token == AND_IF || lxr->token == OR_IF || lxr->token == PIPE)
		return (1);
	while (lxr->token != END_OF_INPUT)
	{
		if (lxr->p_dpt < 0 || parenthesis_check(lxr))
			return (1);
		if (quote_check(lxr))
			return (1);
		lxr = lxr->next;
	}
	if (lxr->p_dpt != 0)
		return (1);
	return (0);
}

int	parser(char *s, t_shell *shell)
{
	t_lxr_lst	*lxr;

	lxr = NULL;
	if (lexer(&lxr, s))
	{
		lxr_lst_clear(&lxr);
		return (1);
	}
	set_final_tokens(lxr);
	if (checker_lxr(lxr))
	{
		lxr_lst_clear(&lxr);
		return (1);
	}
	shell->ast = complete_command_r(&lxr);
	lxr_lst_clear(&lxr);
	if (!shell->ast)
		return (1);
	if (expand(shell->ast, shell->env))
		return (1);
	if (update_quotes(shell->ast))
		return (1);
	return (0);
}
