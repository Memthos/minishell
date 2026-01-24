/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_base_rules.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 16:03:21 by mperrine          #+#    #+#             */
/*   Updated: 2026/01/24 21:05:54 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	complete_command_r(t_list *lst)
{}

int	and_or_r(t_list *lst)
{}

int	pipe_sequence_r(t_list *lst)
{}

int	newline_list_r(t_list *lst, t_list **cmd)
{}

int	linebreak_r(t_list *lst)
{}

complete_command : and_or newline_list
				 | and_or

and_or			 : and_or AND_IF linebreak(optional) pipe_sequence
				 | and_or OR_IF  linebreak(optional) pipe_sequence
				 |  								 pipe_sequence

pipe_sequence	 : pipe_sequence '|' linebreak(optional) simple_command
				 | 										 simple_command

newline_list	 : 				NEWLINE
				 | newline_list NEWLINE

linebreak		 : newline_list
				 | empty (mean optional)
