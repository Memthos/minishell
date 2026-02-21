/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 22:31:18 by mperrine          #+#    #+#             */
/*   Updated: 2026/02/21 14:43:34 by mperrine         ###   ########.fr       */
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

static int	remove_quotes(t_lxr_lst *lxr, size_t quotes_rmv)
{
	t_quote_t	quote_state;
	size_t		i;
	size_t		j;
	char		*str;

	str = malloc(sizeof(char) * (ft_strlen(lxr->data) - quotes_rmv + 1));
	if (!str)
		return (1);
	i = 0;
	j = 0;
	quote_state = 0;
	while (lxr->data[i])
	{
		if (!set_quote_state(&quote_state, lxr->data[i]))
		{
			str[j] = lxr->data[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
	free(lxr->data);
	lxr->data = str;
	return (0);
}

void	set_final_tokens(t_lxr_lst *lxr)
{
	size_t	i;

	if (!lxr)
		return ;
	while (lxr)
	{
		set_io_number(lxr);
		set_assignment_w(lxr);
		if (lxr->data)
		{
			i = 0;
			while (lxr->data[i])
			{
				if (lxr->data[i] == '*')
					lxr->token == WILDCARD;
				i++;
			}
		}
		lxr = lxr->next;
	}
}

int	update_quotes(t_lxr_lst *lxr)
{
	size_t		i;
	t_quote_t	quote_state;
	size_t		quotes_rmv;

	while (lxr)
	{
		if (lxr->data)
		{
			i = 0;
			quote_state = 0;
			quotes_rmv = 0;
			while (lxr->data[i++])
			{
				if (set_quote_state(&quote_state, lxr->data[i - 1]))
					quotes_rmv++;
			}
			if (quotes_rmv % 2 == 0)
			{
				if (remove_quotes(lxr, quotes_rmv))
					return (1);
			}
		}
		lxr = lxr->next;
	}
	return (0);
}
