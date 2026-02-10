/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 12:53:01 by mperrine          #+#    #+#             */
/*   Updated: 2026/02/10 17:39:17 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	parenthesis_check(t_lxr_lst *lxr)
{
	long	diff;

	diff = lxr->p_dpt - lxr->next->p_dpt;
	if (diff < 0 && (lxr->token == AND_IF || lxr->token == OR_IF
		|| lxr->token == PIPE))
		return (0);
	else if (diff > 0 && (lxr->next->token == AND_IF
		|| lxr->next->token == OR_IF || lxr->next->token == PIPE))
		return (0);
	return (1);
}

static int	checker_lxr(t_lxr_lst *lxr)
{
	while (lxr->token != END_OF_INPUT)
	{
		if (lxr->p_dpt != lxr->next->p_dpt && parenthesis_check(lxr))
			return (1);
		//Add quote state to struct to be able to check invalid words
		lxr = lxr->next;
	}
	if (lxr->p_dpt > 0)
		return (1);
	return (0);
}

void	parser(char *s)
{
	t_lxr_lst	*lxr;
	t_ast_lst	*ast;
	int			ret;

	lxr = NULL;
	ret = 0;
	lexer(&lxr, s, &ret);
	free(s);
	if (!lxr || ret || checker_lxr(lxr))
	{
		lxr_lst_clear(&lxr);
		exit(1);
	}
	ast = complete_command_r(&lxr);
}
