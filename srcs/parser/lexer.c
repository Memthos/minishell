/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 01:24:12 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/18 14:23:01 by mperrine         ###   ########.fr       */
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
	if (s[0] == '&' && s[1] == '&')
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
	else if (s[0] == '(')
		return (L_PAREN);
	else if (s[0] == ')')
		return (R_PAREN);
	else
		return (0);
}

static int	check_parenth_dpt(long *parenth_dpt, char c)
{
	if (c == '(')
	{
		(*parenth_dpt)++;
		return (1);
	}
	else if (c == ')')
	{
		(*parenth_dpt)--;
		return (1);
	}
	return (0);
}

static t_status	add_operator(t_lxr_lst **lxr, char *s, size_t *i, long p_dpt)
{
	t_status	ret;

	ret = SUCCESS;
	if (get_operator(s) < 6)
	{
		ret = lxr_lst_add(lxr, make_str(s, 2), get_operator(s), p_dpt);
		(*i)++;
	}
	else
		ret = lxr_lst_add(lxr, make_str(s, 1), get_operator(s), p_dpt);
	return (ret);
}

void	lexer(t_lxr_lst **lxr, char *s, t_status *status)
{
	t_quote_t	quote_state;
	long		p_dpt;
	size_t		i;

	i = 0;
	p_dpt = 0;
	quote_state = NONE;
	while (s[i++] && !*status)
	{
		set_quote_state(&quote_state, s[i - 1]);
		check_parenth_dpt(&p_dpt, s[i - 1]);
		if (quote_state == NONE && s[i - 1] == ' ')
			*status = lxr_lst_add(lxr, NULL, TOKEN, p_dpt);
		else if (quote_state == NONE&& get_operator(&s[i - 1]))
			*status = add_operator(lxr, &s[i - 1], &i, p_dpt);
		else if (quote_state == NONE && is_newline(&s[i - 1], &i))
			*status = lxr_lst_add(lxr, make_str(&s[i - 2], 2), NEW_LINE, p_dpt);
		else if (lxr && *lxr && lxr_lst_last(*lxr)->token == WORD)
			*status = lxr_lst_append(lxr, s[i - 1], TOKEN);
		else
			*status = lxr_lst_add(lxr, make_str(&s[i - 1], 1), WORD, p_dpt);
	}
	if (!*status)
		*status = lxr_lst_add(lxr, NULL, END_OF_INPUT, p_dpt);
	free(s);
}
