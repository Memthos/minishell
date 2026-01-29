/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_command_rules.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 19:12:47 by mperrine          #+#    #+#             */
/*   Updated: 2026/01/29 19:32:08 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*cmd_suffix_r(t_lxr_lst **lxr)
{
	char		*str;
	t_lxr_lst	*consumed;
//					 io_redirect
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

static char	*cmd_prefix_r(t_lxr_lst **lxr)
{
	char		*str;
	t_lxr_lst	*consumed;
//					 io_redirect
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
