/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 01:24:12 by mperrine          #+#    #+#             */
/*   Updated: 2026/01/24 03:09:57 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	t_quote_t	check_quote(char c, int *index)
{
	if (c == '"')
	{
		*index++;
		return (D_QUOTE);
	}
	else if (c == "'")
	{
		*index++;
		return (S_QUOTE);
	}
	return (0);
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
		in_quote = check_quote(s[i - 1], &i);
		if (s[i - 1] == '$' && in_quote != D_QUOTE)
			lst_add(&lst, "CHAR", ASSIGNMENT_W);
	}
	return (NULL);
}

int	main(void)
{
	lexer("abc");
}
