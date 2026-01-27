/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_base_rules.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 16:03:21 by mperrine          #+#    #+#             */
/*   Updated: 2026/01/27 13:49:58 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	complete_command_r(t_list *lst)
{

}

int	and_or_r(t_list *lst)
{}

int	pipe_sequence_r(t_list *lst)
{}

int	newline_list_r(t_list *lst, t_list **cmd)
{}

int	linebreak_r(t_list *lst)
{}

complete_command 	: and_or newline_list
				 	| and_or

and_or			 	: pipe_sequence and_or_tail

and_or_tail			: 'AND_IF' linebreak(optional) pipe_sequence and_or_tail
					| 'OR_IF' linebreak(optional) pipe_sequence and_or_tail
					| empty


pipe_sequence	 	: simple_command pipe_sequence_tail

pipe_sequence_tail	: 'PIPE' linebreak(optional) simple_command pipe_sequence_tail
				 	| empty

newline_list		: 'NEWLINE' newline_list_tail

newline_list_tail	: 'NEWLINE' newline_list_tail
					| empty

linebreak		 	: newline_list_tail
