/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_command_rules.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 19:12:47 by mperrine          #+#    #+#             */
/*   Updated: 2026/01/27 13:49:55 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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


cmd_word		 : 'WORD'
				 | empty

cmd_prefix		 : cmd_prefix_item cmd_prefix
				 | empty

cmd_suffix		 : cmd_suffix_item cmd_suffix
				 | empty

cmd_prefix_item	 : io_redirect
				 | 'ASSIGNMENT_W'

cmd_suffix_item	 : io_redirect
				 | 'WORD'

//if (!contain '=' || no char before '=')->WORD, else if (char before '=' VALID)->ASSIGNMENT_W, else WORD
