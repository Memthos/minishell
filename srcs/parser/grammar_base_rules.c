/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_base_rules.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 16:03:21 by mperrine          #+#    #+#             */
/*   Updated: 2026/01/27 16:01:30 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"




// complete_command 	: and_or newline_list
				 	//  | and_or
t_cmd	*complete_command_r(t_list *lst)
{
	t_cmd	*cmd;

	cmd = NULL;
	and_or_r(&lst, &cmd);
	if (lst && lst->token == NEW_LINE)
		newline_list_r(&lst);
	return (cmd);
}


// and_or			 	: pipe_sequence and_or_tail

// and_or_tail			: 'AND_IF' linebreak(optional) pipe_sequence and_or_tail
// 						| 'OR_IF' linebreak(optional) pipe_sequence and_or_tail
// 						| empty
void	and_or_r(t_list **lst, t_cmd **cmd)
{
	pipe_sequence_r(lst, cmd);
	while ((*lst)->token == AND_IF || (*lst)->token == OR_IF)
	{
		(*lst) = (*lst)->next;
		if ((*lst)->token == NEW_LINE)
			linebreak_r(lst, cmd);

	}
}

// pipe_sequence	 	: simple_command pipe_sequence_tail

// pipe_sequence_tail	: 'PIPE' linebreak(optional) simple_command pipe_sequence_tail
				 	 // | empty
void	pipe_sequence_r(t_list **lst, t_cmd **cmd)
{}

// linebreak		 	: newline_list_tail
void	linebreak_r(t_list **lst, t_cmd **cmd)




newline_list		: 'NEWLINE' newline_list_tail

newline_list_tail	: 'NEWLINE' newline_list_tail
					| empty
