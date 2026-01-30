/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_command_rules.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 19:12:47 by mperrine          #+#    #+#             */
/*   Updated: 2026/01/30 16:16:55 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_ast_lst	*cmd_suffix_r(t_lxr_lst **lxr)
{
	char		*node;
//					 io_redirect
	while (peek(lxr, IO_NUMBER) || peek(lxr, WORD))
	{
		if (!str)
		{
			str = ft_strcpy((*lxr)->data);
			if (!str)
			return (NULL);//FREE
		}
		else
			ft_strjoin_sep(&str, (*lxr)->data, ' ');
		consume(lxr);
	}
	return (str);
}

static t_ast_lst	*cmd_word_r(t_lxr_lst **lxr)
{
	char		*str;

	str = NULL;
	if (peek(lxr, WORD) || peek(lxr, ASSIGNMENT_W))
	{
		str = ft_strcpy((*lxr)->data);
		consume(lxr);
	}
	return (str);
}

static t_ast_lst	*cmd_prefix_r(t_lxr_lst **lxr)
{
	char		*str;

	str = NULL;
//					 io_redirect
	while (peek(lxr, IO_NUMBER) || peek(lxr, WORD))
	{
		if (!str)
		{
			str = ft_strcpy((*lxr)->data);
			if (!str)
			return (NULL);//FREE
		}
		else
			ft_strjoin_sep(&str, (*lxr)->data, ' ');
		consume(lxr);
	}
	return (str);
}

t_ast_lst	*simple_command_r(t_lxr_lst **lxr)
{
	t_ast_lst	*node;

	node = ast_lst_new(cmd_prefix_r(lxr), (*lxr)->token, (*lxr)->p_dpt);
	if (!node)
		return (NULL);
	if (node->data)
		ft_strjoin_sep(node->data, cmd_word_r(lxr), ' ');
	else
		node->data = cmd_word_r(lxr);
	if (node->data)
		ft_strjoin_sep(node->data, cmd_suffix_r(lxr), ' ');
	else
		node->data = cmd_suffix_r(lxr);
	return (node);
}
