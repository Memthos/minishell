/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 16:37:25 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/23 20:05:32 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	can_expand(t_ast_lst *node)
{
	char	*s;

	if (!node->data || node->expand_state == DENY
		|| (node->token != WORD && node->token != WILDCARD))
		return (0);
	s = ft_strchr(node->data, '$');
	if (!s)
		return (0);
	s++;
	if (ft_isalpha(s[0]) || s[0] == '_')
		return (1);
	else if (s[0] == '?' || s[0] == '@' || s[0] == '*' || s[0] == '#'
		|| s[0] == '$' || s[0] == '!' || s[0] == '-' || s[0] == '_'
		|| ft_isdigit(s[0]))
		return (1);
	return (0);
}

int	get_quotes_rmv(t_ast_lst *ast, size_t *quotes_rmv)
{
	size_t		i;
	t_quote_t	quote_state;

	i = 0;
	quote_state = NONE;
	while (ast->data[i])
	{
		if (set_quote_state(&quote_state, ast->data[i]))
			(*quotes_rmv)++;
		if (quote_state == S_QUOTE)
			return (0);
		i++;
	}
	return (1);
}

t_status	shift_ast(t_ast_lst *node)
{
	// t_status	status;
	// t_ast_lst	*right;
	// t_ast_lst	*left;

	// status = SUCCESS;
	// right = node->right;
	// left = node->left;
	// if (right)
	// {
	// 	*node = (t_ast_lst) {right->data, right->token, right->expand_state,
	// 		left, right->right};
	// 	if (right->left)
	// 		ast_lst_clear(&right->left);
	// 	free(right);
	// }
	// else
	// {
	// }
	(void)node;
	return (SUCCESS);
	// return (status);
}
