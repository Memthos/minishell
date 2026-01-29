/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:47:29 by mperrine          #+#    #+#             */
/*   Updated: 2026/01/29 17:02:34 by mperrine         ###   ########.fr       */
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
	int		ret;

	if (lxr->token != ASSIGNMENT_W)
		return ;
	i = 0;
	ret = 0;
	if (!ft_isalpha(lxr->data[i]))
		ret = 1;
	while (!ret && lxr->data[i] && (ft_isalpha(lxr->data[i])
		|| ft_isdigit(lxr->data[i]) || lxr->data[i] == '_'))
		i++;
	if (ret || lxr->data[i] != '=')
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

int	check_quote(t_quote_t *state, char c)
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
		return (1);
	}
	if (*state == D_QUOTE)
		return (0);
	else if (*state == S_QUOTE)
		*state = 0;
	else
		*state = S_QUOTE;
	return (1);
}
