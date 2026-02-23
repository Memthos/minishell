/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 22:31:18 by mperrine          #+#    #+#             */
/*   Updated: 2026/02/23 14:51:00 by mperrine         ###   ########.fr       */
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

static int	remove_quotes(t_ast_lst *ast, size_t quotes_rmv)
{
	t_quote_t	quote_state;
	size_t		i;
	size_t		j;
	char		*str;

	str = malloc(sizeof(char) * (ft_strlen(ast->data) - quotes_rmv + 1));
	if (!str)
		return (1);
	i = 0;
	j = 0;
	quote_state = 0;
	while (ast->data[i])
	{
		if (!set_quote_state(&quote_state, ast->data[i]))
		{
			str[j] = ast->data[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
	free(ast->data);
	ast->data = str;
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
					lxr->token = WILDCARD;
				i++;
			}
		}
		lxr = lxr->next;
	}
}

int	update_quotes(t_ast_lst *ast)
{
	size_t		i;
	t_quote_t	quote_state;
	size_t		quotes_rmv;

	if (!ast || !ast->data)
		return (0);
	i = 0;
	quote_state = 0;
	quotes_rmv = 0;
	while (ast->data[i++])
	{
		if (set_quote_state(&quote_state, ast->data[i - 1]))
			quotes_rmv++;
	}
	if (quotes_rmv % 2 == 0)
	{
		if (remove_quotes(ast, quotes_rmv))
			return (1);
	}
	if (update_quotes(ast->left))
		return (1);
	if (update_quotes(ast->right))
		return (1);
	return (0);
}
