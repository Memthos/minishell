/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 13:42:58 by mperrine          #+#    #+#             */
/*   Updated: 2026/02/20 22:31:16 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	set_quote_state(t_quote_t *quote, char c)
{
	if (c != '"' && c != 39)
		return (0);
	if (c == '"')
	{
		if (*quote == S_QUOTE)
			return (0);
		else if (*quote == D_QUOTE)
			*quote = 0;
		else
			*quote = D_QUOTE;
		return (1);
	}
	if (*quote == D_QUOTE)
		return (0);
	else if (*quote == S_QUOTE)
		*quote = 0;
	else
		*quote = S_QUOTE;
	return (1);
}

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
