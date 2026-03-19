/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lxr_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 17:01:37 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/19 19:01:10 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_status	operator_check(t_lxr_lst *lxr)
{
	if (lxr->token == AND_IF || lxr->token == OR_IF || lxr->token == PIPE)
	{
		if (!lxr->next)
			parser_error_print(lxr->data);
		else if (!lxr->next || lxr->next->token == AND_IF
			|| lxr->next->token == OR_IF || lxr->next->token == PIPE)
			parser_error_print(lxr->next->data);
		else
			return (SUCCESS);
		return (OPERATOR_FAILURE);
	}
	return (SUCCESS);
}

static t_status	l_parenthesis_check(t_lxr_lst *lxr)
{
	if (!lxr->next && lxr->p_dpt > 0)
	{
		parser_error_print("(");
		return (PARENTHESIS_FAILURE);
	}
	else if (lxr->token == L_PAREN)
	{
		if (!lxr->next)
			parser_error_print(lxr->data);
		else if (lxr->next->token == R_PAREN)
			parser_error_print(lxr->next->data);
		else
			return (SUCCESS);
		return (PARENTHESIS_FAILURE);
	}
	else if ((lxr->token == WORD || lxr->token == WILDCARD) && lxr->next
		&& lxr->next->token == L_PAREN)
	{
		parser_error_print(lxr->next->data);
		return (PARENTHESIS_FAILURE);
	}
	return (SUCCESS);
}

static t_status	r_parenthesis_check(t_lxr_lst *lxr)
{
	if (lxr->p_dpt < 0)
	{
		parser_error_print(lxr->data);
		return (PARENTHESIS_FAILURE);
	}
	else if (lxr->token == R_PAREN)
	{
		if (!lxr->next || lxr->next->token != L_PAREN)
			return (SUCCESS);
		parser_error_print(lxr->next->data);
		return (PARENTHESIS_FAILURE);
	}
	return (SUCCESS);
}

static t_status	quote_check(t_lxr_lst *lxr)
{
	size_t		i;
	t_quote_t	quote_state;

	if (!lxr->data)
		return (SUCCESS);
	i = 0;
	quote_state = NONE;
	while (lxr->data[i])
	{
		set_quote_state(&quote_state, lxr->data[i]);
		i++;
	}
	if (quote_state == D_QUOTE)
		parser_error_print("'");
	else if (quote_state == S_QUOTE)
		parser_error_print("\"");
	else
		return (SUCCESS);
	return (QUOTES_FAILURE);
}

void	checker_lxr(t_lxr_lst *lxr, t_status *status)
{
	if (!lxr)
		return ;
	if (lxr->token == AND_IF || lxr->token == OR_IF || lxr->token == PIPE)
	{
		parser_error_print(lxr->data);
		*status = OPERATOR_FAILURE;
	}
	while (!*status && lxr)
	{
		*status = operator_check(lxr);
		if (!*status)
			*status = l_parenthesis_check(lxr);
		if (!*status)
			*status = r_parenthesis_check(lxr);
		if (!*status)
			*status = quote_check(lxr);
		lxr = lxr->next;
	}
}
