/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_command_rules.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 19:12:47 by mperrine          #+#    #+#             */
/*   Updated: 2026/01/29 11:08:57 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"








/////////////////////////////////
// ADD SPACE TO STRJOIN BETWEEN S1 AND S2
// MAKE STRCPY WITH ALLOCATION INSIDE
////////////////////////////////


// cmd_suffix		 : cmd_suffix_item cmd_suffix
				 //  | empty
// cmd_suffix_item	 : io_redirect
				 //  | 'WORD'
static char	*cmd_suffix_r(t_lxr_lst **lxr)
{
	char	*str;
	t_lxr_lst	*consumed;

	while (peek(lxr, IO_NUMBER) || peek(lxr, WORD))
	{
		consumed = consume(lxr);
		if (!str)
		{
			str = ft_strcpy(consumed->data);
			if (!str)
				return (NULL);//FREE
		}
		else
			ft_strjoin_sep(&str, consumed->data, ' ');
		free(consumed->data);
		free(consumed);
	}
	return (str);
}

// cmd_word		 	 : 'WORD'
			 	 //  | empty
//if (!contain '=' || no char before '=')->WORD, else if (char before '=' VALID)->ASSIGNMENT_W, else WORD
static char	*cmd_word_r(t_lxr_lst **lxr)
{
	t_lxr_lst	*consumed;
	char		*str;

	str = NULL;
	if (peek(lxr, WORD))
	{
		consumed = consume(lxr);
		str = ft_strcpy(consumed->data);
		free(consumed->data);
		free(consumed);
	}
	return (str);
}

// cmd_prefix		 : cmd_prefix_item cmd_prefix
				 //  | empty
// cmd_prefix_item	 : io_redirect
				 //  | 'ASSIGNMENT_W'
static char	*cmd_prefix_r(t_lxr_lst **lxr)
{
	char	*str;
	t_lxr_lst	*consumed;

	while (peek(lxr, IO_NUMBER) || peek(lxr, WORD))
	{
		consumed = consume(lxr);
		if (!str)
		{
			str = ft_strcpy(consumed->data);
			if (!str)
				return (NULL);//FREE
		}
		else
			ft_strjoin_sep(&str, consumed->data, ' ');
		free(consumed->data);
		free(consumed);
	}
	return (str);
}

// simple_command	 : cmd_prefix cmd_word cmd_suffix
t_ast_lst	*simple_command_r(t_lxr_lst **lst)
{
	cmd_prefix_r(lst);
	cmd_word_r(lst);
	cmd_suffix_r(lst);
}
