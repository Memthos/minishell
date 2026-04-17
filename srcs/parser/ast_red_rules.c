/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_red_rules.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 19:09:08 by mperrine          #+#    #+#             */
/*   Updated: 2026/04/17 11:06:18 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	limiter_quotes(t_ast_lst *red, t_side side)
{
	t_string	s;
	size_t	i;

	s = ast_lst_last(red, side)->data;
	if (!s)
		return (1);
	i = 0;
	while (s[i])
	{
		if (s[i] == '"' || s[i] == 39)
			return (1);
		i++;
	}
	return (0);
}

int	is_heredoc(t_ast_lst *red, t_side side)
{
	while (red)
	{
		if (red->token == DLESS)
			return (1);
		if (side == LEFT)
			red = red->left;
		else
			red = red->right;
	}
	return (0);
}

int	is_io_redirect(t_lxr_lst **lxr)
{
	if (!lxr || !*lxr)
		return (0);
	if (peek(lxr, LESS))
		return (1);
	else if (peek(lxr, GREAT))
		return (1);
	else if (peek(lxr, DGREAT))
		return (1);
	else if (peek(lxr, DLESS))
		return (1);
	else
		return (0);
}

t_ast_lst	*io_redirect_r(t_lxr_lst **lxr, t_status *status, t_side side)
{
	t_ast_lst	*red;

	red = NULL;
	if (!*status && is_io_redirect(lxr))
		red = ast_lst_new(lxr, status);
	else
		*status = BAD_ARG;
	if (!*status && peek(lxr, WORD) && side == LEFT)
		red->left = ast_lst_new(lxr, status);
	else if (!*status && peek(lxr, WORD) && side == RIGHT)
		red->right = ast_lst_new(lxr, status);
	else
		*status = BAD_ARG;
	if (*status)
	{
		if (*lxr)
			parser_error_print((*lxr)->data);
		else
			parser_error_print("newline");
		ast_lst_clear(&red);
	}
	return (red);
}
