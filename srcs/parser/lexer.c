/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 01:24:12 by mperrine          #+#    #+#             */
/*   Updated: 2026/01/28 14:09:03 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static void	add_lst_operator(t_list **lst, char *s, size_t *index, size_t p_dpt)
{
	if (get_operator(s) == ASSIGNMENT_W)
		lst_append(lst, s[0], ASSIGNMENT_W);
	else if (get_operator(s) < 7)
	{
		lst_add(lst, make_str(s, 2), get_operator(s), p_dpt);
		(*index)++;
	}
	else
		lst_add(lst, make_str(s, 1), get_operator(s), p_dpt);
}

void	lexer(t_list **lst, char *s)
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
			lst_add(lst, NULL, TOKEN, parenth_dpt);
		else if (s[i - 1] == '$' && in_quote != S_QUOTE)
			lst_add(lst, make_str(&s[i - 1], 1), ASSIGNMENT_W, parenth_dpt);
		else if (!in_quote && get_operator(&s[i - 1]))
			add_lst_operator(lst, &s[i - 1], &i, parenth_dpt);
		else if (!in_quote && is_newline(&s[i - 1], &i))
			lst_add(lst, make_str(&s[i - 2], 2), NEW_LINE, parenth_dpt);
		else if (lst && *lst && (lst_last(*lst)->token == WORD
				|| lst_last(*lst)->token == ASSIGNMENT_W))
			lst_append(lst, s[i - 1], TOKEN);
		else
			lst_add(lst, make_str(&s[i - 1], 1), WORD, parenth_dpt);
	}
	lst_add(lst, NULL, END_OF_INPUT, parenth_dpt);
}
