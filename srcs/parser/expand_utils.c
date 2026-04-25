/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 16:37:25 by mperrine          #+#    #+#             */
/*   Updated: 2026/04/25 17:27:20 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	can_expand(t_ast_lst *node, t_status *status, t_shell *shell)
{
	t_string	s;

	if (!node->data || node->expand_state == DENY
		|| (node->token != WORD && node->token != WILDCARD))
		return (0);
	if (node->data[0] == '~')
	{
		if (dict_get(shell->env, "HOME"))
			return (1);
		error_output(NULL, "HOME not set", NO_ERR_MSG);
		*status = FAILURE;
		return (0);
	}
	s = ft_strchr(node->data, '$');
	if (s && s[1] && ft_isspace(s[1]) == 0)
		return (1);
	return (0);
}

size_t	get_quotes_rmv(t_ast_lst *node)
{
	size_t		i;
	size_t		quotes_rmv;
	t_quote_t	quote_state;

	if (!node || !node->data)
		return (0);
	i = 0;
	quotes_rmv = 0;
	quote_state = NONE;
	while (node->data[i])
	{
		if (set_quote_state(&quote_state, node->data[i]))
			quotes_rmv++;
		i++;
	}
	return (quotes_rmv);
}

int	is_redirection(t_ast_lst *node)
{
	if (!node)
		return (0);
	if (node->token == DLESS || node->token == DGREAT
		|| node->token == LESS || node->token == GREAT)
		return (1);
	return (0);
}

t_status	expand_to_ast(t_lxr_lst **lxr, t_ast_lst *ast)
{
	t_status	status;

	status = SUCCESS;
	ast->data = ft_strdup((*lxr)->data);
	if (!ast->data)
		return (ALLOCATION_FAILURE);
	consume(lxr);
	ast->token = WORD;
	ast->expand_state = DENY;
	ast->right = NULL;
	while (!status && *lxr)
	{
		ast_lst_last(ast, RIGHT)->right = ast_lst_new(lxr, &status);
		if (status)
			break ;
		ast_lst_last(ast, RIGHT)->token = WORD;
		ast_lst_last(ast, RIGHT)->expand_state = DENY;
	}
	return (status);
}
