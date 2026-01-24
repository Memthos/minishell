/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_redirect_rules.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 19:09:08 by mperrine          #+#    #+#             */
/*   Updated: 2026/01/24 21:16:59 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	io_redirect_r(t_list *lst)
{}

int	io_file_r(t_list *lst)
{}

int	filename_r(t_list *lst)
{}

int	io_here_r(t_list *lst)
{}

int	here_end_r(t_list *lst)
{}

io_redirect		 : IO_NUMBER io_file
				 |  		 io_file
				 | IO_NUMBER io_here
				 |  		 io_here

io_file			 : '<'    filename
				 | '>'    filename
				 | DGREAT filename

filename		 : WORD //"Expansion to have only one field(one filename)"

io_here			 : DLESS here_end

here_end		 : WORD //"Determine delimiter for here-document"
