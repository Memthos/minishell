/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:47:29 by mperrine          #+#    #+#             */
/*   Updated: 2026/02/11 13:46:30 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"



char	*make_str(char *input, size_t len)
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

int	check_quote(t_lxr_p *p, char c)
{
	if (c != '"' && c != 39)
		return (0);
	if (c == '"')
	{
		if (p->quote == S_QUOTE)
			return (0);
		else if (p->quote == D_QUOTE)
			p->quote = 0;
		else
			p->quote = D_QUOTE;
		return (1);
	}
	if (p->quote == D_QUOTE)
		return (0);
	else if (p->quote == S_QUOTE)
		p->quote = 0;
	else
		p->quote = S_QUOTE;
	return (1);
}
