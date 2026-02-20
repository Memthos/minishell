/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 13:42:58 by mperrine          #+#    #+#             */
/*   Updated: 2026/02/20 21:33:41 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	set_io_number(t_lxr_lst *lxr)
{
	size_t	i;

	if (!lxr->data)
		return ;
	i = 0;
	while (lxr->data[i] && lxr->data[i] >= '0' && lxr->data[i] <= '9')
		i++;
	if (i == ft_strlen(lxr->data)
		&& (lxr->next->token > 4 || lxr->next->token < 9))
		lxr->token = IO_NUMBER;
}

static void	set_assignment_w(t_lxr_lst *lxr)
{
	size_t	i;

	if (!lxr->data)
		return ;
	i = 0;
	if (!ft_isalpha(lxr->data[i]) && lxr->data[i] != '_')
		return ;
	while (lxr->data[i] && (ft_isalnum(lxr->data[i]) || lxr->data[i] == '_'))
		i++;
	if (lxr->data[i] == '=')
		lxr->token = ASSIGNMENT_W;
}

void	set_final_tokens(t_lxr_lst *lxr)
{
	if (!lxr)
		return ;
	while (lxr)
	{
		set_io_number(lxr);
		set_assignment_w(lxr);
		lxr = lxr->next;
	}
}

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
