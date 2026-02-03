/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_red_rules.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 19:09:08 by mperrine          #+#    #+#             */
/*   Updated: 2026/02/03 16:30:42 by mperrine         ###   ########.fr       */
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
		return(0);
}

t_ast_lst	*io_file_r(t_lxr_lst **lxr)
{}

t_ast_lst	*filename_r(t_lxr_lst **lxr)
{}

t_ast_lst	*io_here_r(t_lxr_lst **lxr)
{}

t_ast_lst	*here_end_r(t_lxr_lst **lxr)
{}


t_ast_lst	*io_redirect_r(t_lxr_lst **lxr)
{
	t_ast_lst	*cmd;
	char		*data;

	if (peek(lxr, IO_NUMBER))
	{
		data = ft_strcpy((*lxr)->data);
		cmd = ast_lst_new(data, (*lxr)->token, (*lxr)->p_dpt);
		consume(lxr);
	}
	if (peek(lxr, DLESS))
	{

	}
}

io_redirect		 : 'IO_NUMBER' io_file
				 |  		   io_file
				 | 'IO_NUMBER' io_here
				 |  		   io_here

io_file			 : 'LESS'   filename
				 | 'GREAT'  filename
				 | 'DGREAT' filename

filename		 : 'WORD' //"Expansion to have only one field(one filename)"

io_here			 : 'DLESS' here_end

here_end		 : 'WORD' //"Determine delimiter for here-document"
