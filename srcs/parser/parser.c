/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 12:53:01 by mperrine          #+#    #+#             */
/*   Updated: 2026/02/23 16:54:08 by juperrin         ###   ########.fr       */
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
			return (FAILURE);
	}
	else if (lxr->token == R_PAREN)
	{
		if (lxr->next && (lxr->next->token == WORD
				|| lxr->next->token == WILDCARD
				|| lxr->next->token == ASSIGNMENT_W
				|| lxr->next->token == L_PAREN))
			return (FAILURE);
	}
	else if ((lxr->token == WORD || lxr->token == ASSIGNMENT_W
			|| lxr->token == WILDCARD) && lxr->next
		&& lxr->next->token == L_PAREN)
		return (FAILURE);
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
		return (FAILURE);
	return (SUCCESS);
}

static int	checker_lxr(t_lxr_lst *lxr)
{
	if (!lxr)
		return (FAILURE);
	if (lxr->token == AND_IF || lxr->token == OR_IF || lxr->token == PIPE)
		return (FAILURE);
	while (lxr->token != END_OF_INPUT)
	{
		if (lxr->p_dpt < 0 || parenthesis_check(lxr))
			return (FAILURE);
		if (quote_check(lxr))
			return (FAILURE);
		lxr = lxr->next;
	}
	if (lxr->p_dpt != 0)
		return (FAILURE);
	return (SUCCESS);
}

int	parser(char *s, t_shell *shell)
{
	t_lxr_lst	*lxr;

	lxr = NULL;
	if (lexer(&lxr, s))
	{
		lxr_lst_clear(&lxr);
		return (FAILURE);
	}
	set_final_tokens(lxr);
	if (checker_lxr(lxr))
	{
		lxr_lst_clear(&lxr);
		return (FAILURE);
	}
	shell->cmd_ast = complete_command_r(&lxr);
	lxr_lst_clear(&lxr);
	if (!shell->cmd_ast)
		return (FAILURE);
	if (expand(shell->cmd_ast, shell->env))
		return (FAILURE);
	if (update_quotes(shell->cmd_ast))
		return (FAILURE);
	return (SUCCESS);
}
