/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 01:24:12 by mperrine          #+#    #+#             */
/*   Updated: 2026/01/27 13:49:44 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static	int	check_quote(t_quote_t *state, char c, size_t *index)
{
	if (c != '"' && c != 39)
		return (0);
	if (c == '"')
	{
		if (*state == S_QUOTE)
			return (0);
		else if (*state == D_QUOTE)
			*state = 0;
		else
			*state = D_QUOTE;
		(*index)++;
		return (1);
	}
	if (*state == D_QUOTE)
		return (0);
	else if (*state == S_QUOTE)
		*state = 0;
	else
		*state = S_QUOTE;
	(*index)++;
	return (1);
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
	else if (s[0] == '(')
		return (L_PAREN);
	else if (s[0] == ')')
		return (R_PAREN);
	else
		return (0);
}

static void	add_lst_operator(t_list **lst, char *s, size_t *index)
{
	if (get_operator(s) == ASSIGNMENT_W)
		lst_append(lst, s[0], ASSIGNMENT_W);
	else if (get_operator(s) < 7)
	{
		lst_add(lst, make_str(s, 2), get_operator(s));
		(*index)++;
	}
	else
		lst_add(lst, make_str(s, 1), get_operator(s));
}

void	lexer(t_list **lst, char *s)
{
	t_quote_t	in_quote;
	size_t		i;

	in_quote = 0;
	i = 0;
	while (s[i])
	{
		if (check_quote(&in_quote, s[i], &i))
			lst_add(lst, NULL, TOKEN);
		if (s[i] == '$' && in_quote != S_QUOTE)
			lst_add(lst, make_str(&s[i], 1), ASSIGNMENT_W);
		else if (!in_quote && get_operator(&s[i]))
			add_lst_operator(lst, &s[i], &i);
		else if (!in_quote && s[i] >= 9 && s[i] <= 13)
			lst_add(lst, NULL, NEW_LINE);
		else if (!in_quote && s[i] == ' ')
			lst_add(lst, NULL, TOKEN);
		else if (lst && *lst && (lst_last(*lst)->token == WORD
				|| lst_last(*lst)->token == ASSIGNMENT_W))
			lst_append(lst, s[i], TOKEN);
		else
			lst_add(lst, make_str(&s[i], 1), WORD);
		if (s[i])
			i++;
	}
}
