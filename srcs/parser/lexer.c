/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 01:24:12 by mperrine          #+#    #+#             */
/*   Updated: 2026/01/29 17:06:14 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_newline(char *s, size_t *index)
{
	if (s[0] == '\\' && (s[1] == 't' || s[1] == 'n'
			|| s[1] == 'v' || s[1] == 'f' || s[1] == 'r'))
	{
		(*index)++;
		return (1);
	}
	return (0);
}

static int	get_operator(char *s)
{
	if (s[0] == '=')
		return (ASSIGNMENT_W);
	else if (s[0] == '&' && s[1] == '&')
		return (AND_IF);
	else if (s[0] == '|' && s[1] == '|')
		return (OR_IF);
	else if (s[0] == '<' && s[1] == '<')
		return (DLESS);
	else if (s[0] == '>' && s[1] == '>')
		return (DGREAT);
	else if (s[0] == '<')
		return (LESS);
	else if (s[0] == '>')
		return (GREAT);
	else if (s[0] == '|')
		return (PIPE);
	else
		return (0);
}

static int	check_parenth_dpt(size_t *parenth_dpt, char c)
{
	if (c == '(')
	{
		(*parenth_dpt)++;
		return (1);
	}
	else if (c == ')' && *parenth_dpt > 0)
	{
		(*parenth_dpt)--;
		return (1);
	}
	return (0);
}

static void	add_lxr_operator(t_lxr_lst **lxr, char *s, size_t *i, size_t p_dpt)
{
	if (get_operator(s) == ASSIGNMENT_W)
		lxr_lst_append(lxr, s[0], ASSIGNMENT_W);
	else if (get_operator(s) < 7)
	{
		lxr_lst_add(lxr, make_str(s, 2), get_operator(s), p_dpt);
		(*i)++;
	}
	else
		lxr_lst_add(lxr, make_str(s, 1), get_operator(s), p_dpt);
}

void	lexer(t_lxr_lst **lxr, char *s)
{
	t_quote_t	in_quote;
	size_t		parenth_dpt;
	size_t		i;

	in_quote = 0;
	parenth_dpt = 0;
	i = 0;
	while (s[i++])
	{
		if (check_quote(&in_quote, s[i - 1]) || (!in_quote && s[i - 1] == ' ')
			|| (!in_quote && check_parenth_dpt(&parenth_dpt, s[i - 1])))
			lxr_lst_add(lxr, NULL, TOKEN, parenth_dpt);
		else if (s[i - 1] == '$' && in_quote != S_QUOTE)
			lxr_lst_add(lxr, make_str(&s[i - 1], 1), ASSIGNMENT_W, parenth_dpt);
		else if (!in_quote && get_operator(&s[i - 1]))
			add_lxr_operator(lxr, &s[i - 1], &i, parenth_dpt);
		else if (!in_quote && is_newline(&s[i - 1], &i))
			lxr_lst_add(lxr, make_str(&s[i - 2], 2), NEW_LINE, parenth_dpt);
		else if (lxr && *lxr && (lxr_lst_last(*lxr)->token == WORD
				|| lxr_lst_last(*lxr)->token == ASSIGNMENT_W))
			lxr_lst_append(lxr, s[i - 1], TOKEN);
		else
			lxr_lst_add(lxr, make_str(&s[i - 1], 1), WORD, parenth_dpt);
	}
	lxr_lst_add(lxr, NULL, END_OF_INPUT, parenth_dpt);
}
