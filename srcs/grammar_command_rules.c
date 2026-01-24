/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 19:12:47 by mperrine          #+#    #+#             */
/*   Updated: 2026/01/24 19:12:58 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	simple_command_r(t_list *lst)
{}

int	cmd_name_r(t_list *lst)
{}

int	cmd_word_r(t_list *lst)
{}

int	cmd_prefix_r(t_list *lst)
{}

int	cmd_suffix_r(t_list *lst)
{}

simple_command	 : cmd_prefix cmd_word cmd_suffix
				 | cmd_prefix cmd_word
				 | cmd_prefix
				 | cmd_name cmd_suffix
				 | cmd_suffix

cmd_name		 : WORD //"(first word)-> if (!contain '=')->WORD, else->Rule 7b"

cmd_word		 : WORD //"(!first word)->if (begin with '=')->WORD, else if (char before '=' valid)->ASSIGNMENT_W, else->WORD"

cmd_prefix		 : cmd_prefix io_redirect
				 | 			  io_redirect
				 | cmd_prefix ASSIGNMENT_W
				 |  		  ASSIGNMENT_W

cmd_suffix		 : cmd_suffix io_redirect
				 | 			  io_redirect
				 | cmd_suffix WORD
				 | 			  WORD
