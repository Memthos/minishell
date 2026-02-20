/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 12:53:01 by mperrine          #+#    #+#             */
/*   Updated: 2026/02/20 22:05:32 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static int	quote_check(t_lxr_lst *lxr)
{
}

static int	checker_lxr(t_lxr_lst *lxr)
{
	if (!lxr)
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

static int	remove_quotes(t_lxr_lst *lxr, size_t quotes_rmv)
{
	t_quote_t	quote_state;
	size_t		i;
	size_t		j;
	char		*str;

	str = malloc(sizeof(char) * (ft_strlen(lxr->data) - quotes_rmv + 1));
	if (!str)
		return (1);
	i = 0;
	j = 0;
	quote_state = 0;
	while (lxr->data[i])
	{
		if (!set_quote_state(&quote_state, lxr->data[i]))
		{
			str[j] = lxr->data[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
	free(lxr->data);
	lxr->data = str;
	return (0);
}

static int	update_quotes(t_lxr_lst *lxr)
{
	size_t		i;
	t_quote_t	quote_state;
	size_t		quotes_rmv;

	while (lxr)
	{
		if (lxr->data)
		{
			i = 0;
			quote_state = 0;
			quotes_rmv = 0;
			while (lxr->data[i++])
			{
				if (set_quote_state(&quote_state, lxr->data[i - 1]))
					quotes_rmv++;
			}
			if (quotes_rmv % 2 == 0)
			{
				if (remove_quotes(lxr, quotes_rmv))
					return (1);
			}
		}
		lxr = lxr->next;
	}
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
	if (update_quotes(lxr) || checker_lxr(lxr))
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
