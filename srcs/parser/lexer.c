/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 01:24:12 by mperrine          #+#    #+#             */
/*   Updated: 2026/04/17 11:35:46 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_isspace(t_string s)
{
	if (s[0] == '\n')
		return (0);
	if ((s[0] >= 9 && s[0] <= 13) || s[0] == ' ')
		return (1);
	return (0);
}

static int	get_operator(t_string s)
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

static t_status	add_operator(t_lxr_lst **lxr, t_string s, size_t *i, long p_dpt)
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

void	lexer(t_lxr_lst **lxr, t_string s, t_status *status)
{
	t_quote_t	quote_state;
	long		p_dpt;
	size_t		i;

	i = 0;
	p_dpt = 0;
	quote_state = NONE;
	while (s[i] && !*status)
	{
		set_quote_state(&quote_state, s[i]);
		check_parenth_dpt(&p_dpt, s[i]);
		if (quote_state == NONE && ft_isspace(&s[i]))
			*status = lxr_lst_add(lxr, NULL, TOKEN, p_dpt);
		else if (quote_state == NONE && s[i] == '\n')
			*status = lxr_lst_add(lxr, NULL, NEW_LINE, p_dpt);
		else if (quote_state == NONE && get_operator(&s[i]))
			*status = add_operator(lxr, &s[i], &i, p_dpt);
		else if (lxr && *lxr && lxr_lst_last(*lxr)->token == WORD)
			*status = lxr_lst_append(lxr, s[i]);
		else
			*status = lxr_lst_add(lxr, make_str(&s[i], 1), WORD, p_dpt);
		i++;
	}
	free(s);
}
