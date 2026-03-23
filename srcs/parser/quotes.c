/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 16:56:31 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/23 12:48:45 by mperrine         ###   ########.fr       */
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
			*quote = NONE;
		else
			*quote = D_QUOTE;
		return (1);
	}
	if (*quote == D_QUOTE)
		return (0);
	else if (*quote == S_QUOTE)
		*quote = NONE;
	else
		*quote = S_QUOTE;
	return (1);
}

static t_status	remove_quotes(t_ast_lst *ast, size_t quotes_rmv)
{
	t_quote_t	quote_state;
	size_t		i;
	size_t		j;
	char		*str;

	str = malloc(sizeof(char) * (ft_strlen(ast->data) - quotes_rmv + 1));
	if (!str)
		return (ALLOCATION_FAILURE);
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
	return (SUCCESS);
}

int	remove_node_quotes(t_ast_lst *ast, t_status *status, int is_expand)
{
	size_t	i;
	size_t		quotes_rmv;
	t_quote_t	quote_state;
	int			can_expand;

	if (!ast || !ast->data)
		return (1);
	i = 0;
	quotes_rmv = 0;
	quote_state = NONE;
	can_expand = 1;
	while (ast->data[i++])
	{
		if (set_quote_state(&quote_state, ast->data[i - 1]))
			quotes_rmv++;
		if (quote_state == S_QUOTE)
			can_expand = 0;
	}
	if (is_expand && can_expand == 0)
		return (0);
	else if (quotes_rmv > 0 && quotes_rmv % 2 == 0)
		*status = remove_quotes(ast, quotes_rmv);
	return (can_expand);
}

void	remove_ast_quotes(t_ast_lst *ast, t_status *status)
{
	if (*status || !ast)
		return ;
	if (ast->data && ast->expand_state != DENY)
		remove_node_quotes(ast, status, 0);
	remove_ast_quotes(ast->left, status);
	remove_ast_quotes(ast->right, status);
}
