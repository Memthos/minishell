/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 01:24:12 by mperrine          #+#    #+#             */
/*   Updated: 2026/02/09 15:16:22 by mperrine         ###   ########.fr       */
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
		return (ASSIGNMENT);
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

static int	add_lxr_operator(t_lxr_lst **lxr, char *s, size_t *i, size_t p_dpt)
{
	int	ret;

	ret = 0;
	if (get_operator(s) == ASSIGNMENT)
		ret = lxr_lst_append(lxr, s[0], ASSIGNMENT);
	else if (get_operator(s) < 7)
	{
		ret = lxr_lst_add(lxr, make_str(s, 2), get_operator(s), p_dpt);
		(*i)++;
	}
	else
		ret = lxr_lst_add(lxr, make_str(s, 1), get_operator(s), p_dpt);
	return (ret);
}

void	lexer(t_lxr_lst **lxr, char *s, int *ret)
{
	t_lxr_params	p;

	p = (t_lxr_params){.quote = 0, .p_dpt = 0, .i = 0};
	while (s[p.i++] && !*ret)
	{
		if (!ret && (check_quote(&p, s[p.i - 1])
				|| (!p.quote && s[p.i - 1] == ' ')
				|| (!p.quote && check_parenth_dpt(&p.p_dpt, s[p.i - 1]))))
			*ret = lxr_lst_add(lxr, NULL, TOKEN, p.p_dpt);
		else if (!ret && s[p.i - 1] == '$' && p.quote != S_QUOTE)
			*ret = lxr_lst_add(lxr, make_str(&s[p.i - 1], 1),
					ASSIGNMENT, p.p_dpt);
		else if (!ret && !p.quote && get_operator(&s[p.i - 1]))
			*ret = add_lxr_operator(lxr, &s[p.i - 1], &p.i, p.p_dpt);
		else if (!ret && !p.quote && is_newline(&s[p.i - 1], &p.i))
			*ret = lxr_lst_add(lxr, make_str(&s[p.i - 2], 2),
					NEW_LINE, p.p_dpt);
		else if (!ret && (lxr && *lxr && (lxr_lst_last(*lxr)->token == WORD
					|| lxr_lst_last(*lxr)->token == ASSIGNMENT)))
			*ret = lxr_lst_append(lxr, s[p.i - 1], TOKEN);
		else if (!ret)
			*ret = lxr_lst_add(lxr, make_str(&s[p.i - 1], 1), WORD, p.p_dpt);
	}
	if (!ret)
		*ret = lxr_lst_add(lxr, NULL, END_OF_INPUT, p.p_dpt);
}
