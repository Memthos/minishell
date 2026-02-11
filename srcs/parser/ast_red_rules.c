/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_red_rules.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 19:09:08 by mperrine          #+#    #+#             */
/*   Updated: 2026/02/11 09:35:31 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_io_redirect(t_lxr_lst **lxr)
{
	if (peek(lxr, IO_NUMBER))
		return (1);
	else if (peek(lxr, LESS))
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

t_ast_lst	*io_redirect_r(t_lxr_lst **lxr)
{
	t_ast_lst	*io_red;
	int			i;

	io_red = NULL;
	if (peek(lxr, IO_NUMBER))
		io_red = ast_lst_new(lxr);
	i = 0;
	while (*lxr && i < 2)
	{
		if (io_red)
			io_red->left = ast_lst_new(lxr);
		else
			io_red = ast_lst_new(lxr);
		i++;
	}
	if (i < 2)
		return (NULL);
		//Clear lst
	return (io_red);
}
