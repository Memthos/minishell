/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_base_rules.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 16:03:21 by mperrine          #+#    #+#             */
/*   Updated: 2026/01/29 17:15:37 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"




// complete_command 	: and_or newline_list
				 	//  | and_or
t_ast_lst	*complete_command_r(t_lxr_lst **lxr)
{
	and_or_r(lxr);
}


// and_or			 	: pipe_sequence and_or_tail

// and_or_tail			: 'AND_IF' linebreak(optional) pipe_sequence and_or_tail
// 						| 'OR_IF' linebreak(optional) pipe_sequence and_or_tail
// 						| empty
void	and_or_r(t_lxr_lst **lxr)
{
	pipe_sequence_r(lxr);
}

// pipe_sequence	 	: simple_command pipe_sequence_tail

// pipe_sequence_tail	: 'PIPE' linebreak(optional) simple_command pipe_sequence_tail
				 	 // | empty
void	pipe_sequence_r(t_lxr_lst **lxr)
{
	t_ast_lst	*node;

	if ()
	node = simple_command_r(lxr);
}

// linebreak		 	: newline_list_tail
void	linebreak_r(t_lxr_lst **lxr)




newline_list		: 'NEWLINE' newline_list_tail

newline_list_tail	: 'NEWLINE' newline_list_tail
					| empty
