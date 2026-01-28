/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lxr_lst_append.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:05:46 by juperrin          #+#    #+#             */
/*   Updated: 2026/01/28 23:08:47 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	lxr_lst_append(t_lxr_lst **head, char c, t_token token)
{
	char		*clean_char;
	char		*new_str;
	t_lxr_lst	*tmp;

	if (NULL == head)
		return ;
	clean_char = make_str(&c, 1);
	if (!clean_char)
		return ; //ADD FREE FOR LEXER ETC.
	tmp = lxr_lst_last(*head);
	if (!tmp->data)
		tmp->data = clean_char;
	else
	{
		new_str = ft_strjoin(tmp->data, clean_char);
		free(tmp->data);
		tmp->data = new_str;
	}
	if (token != TOKEN)
		tmp->token = token;
}
