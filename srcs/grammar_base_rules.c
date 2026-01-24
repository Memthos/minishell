/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_rules.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 16:03:21 by mperrine          #+#    #+#             */
/*   Updated: 2026/01/24 19:15:08 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	complete_command_r(t_list *lst)
{}

int	and_or_r(t_list *lst)
{}

int	pipe_sequence_r(t_list *lst)
{}

int	newline_list_r(t_list *lst)
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
