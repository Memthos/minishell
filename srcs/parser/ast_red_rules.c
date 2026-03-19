/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_red_rules.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 19:09:08 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/19 19:52:12 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	limiter_quotes(t_ast_lst *red, t_side side)
{
	char	*s;
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
	if (peek(lxr, IO_NUMBER))
		return (1);
	else if (peek(lxr, LESS))
		return (2);
	else if (peek(lxr, GREAT))
		return (2);
	else if (peek(lxr, DGREAT))
		return (2);
	else if (peek(lxr, DLESS))
		return (2);
	else
		return (0);
}

static t_ast_lst	*main_redirect(t_lxr_lst **lxr, t_status *status,
	t_side side)
{
	t_ast_lst	*red;

	red = NULL;
	if (!*status && is_io_redirect(lxr) == 2)
		red = ast_lst_new(lxr, status);
	else
		*status = REDIRECTION_FAILURE;
	if (!*status && peek(lxr, WORD) && side == LEFT)
		red->left = ast_lst_new(lxr, status);
	else if (!*status && peek(lxr, WORD) && side == RIGHT)
		red->right = ast_lst_new(lxr, status);
	else
		*status = REDIRECTION_FAILURE;
	if (*status)
	{
		if (*lxr)
			parser_error_print((*lxr)->data);
		else
			parser_error_print(NULL);
		ast_lst_clear(&red);
	}
	return (red);
}

t_ast_lst	*io_redirect_r(t_lxr_lst **lxr, t_status *status, t_side side)
{
	t_ast_lst	*io_red;
	t_ast_lst	*red;

	io_red = NULL;
	red = NULL;
	if (peek(lxr, IO_NUMBER))
		io_red = ast_lst_new(lxr, status);
	if (*status)
		return (NULL);
	red = main_redirect(lxr, status, side);
	if (io_red && side == LEFT)
		io_red->left = red;
	else if (io_red && side == RIGHT)
		io_red->right = red;
	else
		io_red = red;
	if (*status)
		ast_lst_clear(&io_red);
	return (io_red);
}
