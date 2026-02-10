/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:47:29 by mperrine          #+#    #+#             */
/*   Updated: 2026/02/10 17:39:12 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_io_number_t(t_lxr_lst *lxr)
{
	size_t	i;

	if (!lxr || !lxr->data)
		return ;
	i = 0;
	while (lxr->data[i] && lxr->data[i] >= '0' && lxr->data[i] <= '9')
		i++;
	if (i == ft_strlen(lxr->data))
		lxr->token = IO_NUMBER;
}

void	check_assignment_w(t_lxr_lst *lxr)
{
	size_t	i;
	int		type;

	if (lxr->token != ASSIGNMENT_W)
		return ;
	i = 0;
	type = 0;
	if (lxr->data[i] == '$')
	{
		i++;
		type = 1;
	}
	if (!ft_isalpha(lxr->data[i]))
	{
		lxr->token = WORD;
		return ;
	}
	while (lxr->data[i] && (ft_isalnum(lxr->data[i]) || lxr->data[i] == '_'))
		i++;
	if ((type == 0 && lxr->data[i] != '=')
		|| (type == 1 && i != ft_strlen(lxr->data)))
		lxr->token = WORD;
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
