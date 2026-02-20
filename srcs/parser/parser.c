/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 12:53:01 by mperrine          #+#    #+#             */
/*   Updated: 2026/02/20 13:35:14 by mperrine         ###   ########.fr       */
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

static void	set_final_tokens(t_lxr_lst *lxr)
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

static int	parenthesis_check(t_lxr_lst *lxr)
{
	if (lxr->next->token != L_PAREN && lxr->token != R_PAREN)
		return (0);
	else if ((lxr->token == AND_IF || lxr->token == OR_IF || lxr->token == PIPE)
		&& lxr->next->token == L_PAREN)
		return (0);
	else if (lxr->token == R_PAREN && (lxr->next->token == AND_IF
			|| lxr->next->token == OR_IF || lxr->next->token == PIPE
			|| lxr->next->token == END_OF_INPUT))
		return (0);
	return (1);
}

static int	checker_lxr(t_lxr_lst *lxr)
{
	if (!lxr)
		return (1);
	while (lxr->token != END_OF_INPUT)
	{
		if (lxr->p_dpt < 0 || parenthesis_check(lxr))
			return (1);
		//quotes
		lxr = lxr->next;
	}
	if (lxr->p_dpt != 0)
		return (1);
	return (0);
}

t_ast_lst	*parser(char *s)
{
	t_lxr_lst	*lxr;
	t_ast_lst	*ast;

	lxr = NULL;
	if (lexer(&lxr, s))
	{
		lxr_lst_clear(&lxr);
		exit(1);
	}
	set_final_tokens(lxr);
	if (checker_lxr(lxr))
	{
		lxr_lst_clear(&lxr);
		exit(1);
	}
	ast = complete_command_r(&lxr);
	lxr_lst_clear(&lxr);
	if (!ast)
		exit(1);
	return (ast);
}
