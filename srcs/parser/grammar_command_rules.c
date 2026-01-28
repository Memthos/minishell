/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_command_rules.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 19:12:47 by mperrine          #+#    #+#             */
/*   Updated: 2026/01/28 15:09:36 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// simple_command	 : cmd_prefix cmd_word cmd_suffix
t_cmd	*simple_command_r(t_list **lst)
{
	cmd_prefix_r(lst);
	cmd_word_r(lst);
	cmd_suffix_r(lst);
}

// cmd_prefix		 : cmd_prefix_item cmd_prefix
				 //  | empty
// cmd_prefix_item	 : io_redirect
				 //  | 'ASSIGNMENT_W'
char	*cmd_prefix_r(t_list **lst)
{
	char	*str;
	char	*tmp;
	t_list	*consumed;

	str = NULL;
	while (peek(lst, IO_NUMBER) || peek(lst, ASSIGNMENT_W))
	{
		consumed = consume(lst);
		if (!str)
			ft_strlcpy(str, consumed->data, ft_strlen(consumed->data));
		else
			tmp = ft_strjoin(str, consumed->data);
		free(consumed->data);
		free(consumed);
		free(str);
		str = tmp;
	}
}

// cmd_word		 	 : 'WORD'
			 	 //  | empty
//if (!contain '=' || no char before '=')->WORD, else if (char before '=' VALID)->ASSIGNMENT_W, else WORD
int	cmd_word_r(t_list **lst)
{}

// cmd_suffix		 : cmd_suffix_item cmd_suffix
				 //  | empty
// cmd_suffix_item	 : io_redirect
				 //  | 'WORD'
int	cmd_suffix_r(t_list **lst)
{}
