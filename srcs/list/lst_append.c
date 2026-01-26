/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_append.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:05:46 by juperrin          #+#    #+#             */
/*   Updated: 2026/01/26 16:08:04 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	lst_append(t_list **head, char c, t_token token)
{
	char	*clean_char;
	char	*new_str;
	t_list	*tmp;

	if (NULL == head)
		return ;
	clean_char = malloc(sizeof(char) * 2);
	if (!clean_char)
		return ; //ADD FREE FOR LEXER ETC.
	clean_char[0] = c;
	clean_char[1] = '\0';
	tmp = lst_last(*head);
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
