/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 01:24:12 by mperrine          #+#    #+#             */
/*   Updated: 2026/01/26 13:30:11 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*make_str(char *input, size_t len)
{
	char	*s;
	size_t	i;

	s = malloc(sizeof(char) * (len + 1));
	if (!s)
		return (NULL);
	s[len] = '\0';
	i = 0;
	while (i++ < len)
		s[i - 1] = input[i - 1];
	return (s);
}

static	t_quote_t	check_quote(char c)
{
	if (c == '"')
		return (D_QUOTE);
	else if (c == 39)
		return (S_QUOTE);
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
	else if (s[0] == '=')
		return (EQUAL);
	else
		return (0);
}

static void	add_lst_operator(t_list **lst, char *s, size_t *index)
{
	if (get_operator(s) < 7)
	{
		lst_add(lst, make_str(s, 2), get_operator(s));
		(*index)++;
	}
	else
		lst_add(lst, make_str(s, 1), get_operator(s));
}

t_list	*lexer(char *s)
{
	t_list		*lst;
	t_quote_t	in_quote;
	size_t		i;

	lst = NULL;
	i = 0;
	while (s[i++])
	{
		in_quote = check_quote(s[i - 1]);
		if (s[i - 1] == '$' && in_quote != D_QUOTE)
			lst_add(&lst, make_str(&s[i - 1], 1), ASSIGNMENT_W);
		else if (!in_quote && get_operator(&s[i - 1]))
			add_lst_operator(&lst, &s[i - 1], &i);
		else if (!in_quote && s[i - 1] >= 9 && s[i - 1] <= 13)
			lst_add(&lst, NULL, NEW_LINE);
		else if (!in_quote && s[i - 1] == ' ')
			lst_add(&lst, NULL, TOKEN);
		else if (lst)
			lst_append(lst_last(lst), s[i - 1]);
		else
			lst_add(&lst, make_str(&s[i - 1], 1), WORD);
	}
	return (lst);
}
