/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 01:24:12 by mperrine          #+#    #+#             */
/*   Updated: 2026/02/20 21:30:39 by mperrine         ###   ########.fr       */
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

static int	add_lxr_operator(t_lxr_lst **lxr, char *s, size_t *i, t_lxr_p *p)
{
	int	ret;

	ret = 0;
	if (get_operator(s) < 7)
	{
		ret = lxr_lst_add(lxr, make_str(s, 2), get_operator(s), p);
		(*i)++;
	}
	else
		ret = lxr_lst_add(lxr, make_str(s, 1), get_operator(s), p);
	return (ret);
}

int	lexer(t_lxr_lst **lxr, char *s)
{
	t_lxr_p	p;

	p = (t_lxr_p){.i = 0, .p_dpt = 0, .quote = 0, .ret = 0};
	while (s[p.i++] && !p.ret)
	{
		if (!p.ret)
		{
			set_quote_state(&p.quote, s[p.i - 1]);
			check_parenth_dpt(&p.p_dpt, s[p.i - 1]);
		}
		if (!p.ret && !p.quote && s[p.i - 1] == ' ')
			p.ret = lxr_lst_add(lxr, NULL, TOKEN, &p);
		else if (!p.ret && !p.quote && get_operator(&s[p.i - 1]))
			p.ret = add_lxr_operator(lxr, &s[p.i - 1], &p.i, &p);
		else if (!p.ret && !p.quote && is_newline(&s[p.i - 1], &p.i))
			p.ret = lxr_lst_add(lxr, make_str(&s[p.i - 2], 2), NEW_LINE, &p);
		else if (!p.ret && lxr && *lxr && lxr_lst_last(*lxr)->token == WORD)
			p.ret = lxr_lst_append(lxr, s[p.i - 1], TOKEN);
		else if (!p.ret)
			p.ret = lxr_lst_add(lxr, make_str(&s[p.i - 1], 1), WORD, &p);
	}
	if (!p.ret)
		p.ret = lxr_lst_add(lxr, NULL, END_OF_INPUT, &p);
	free(s);
	return (p.ret);
}
