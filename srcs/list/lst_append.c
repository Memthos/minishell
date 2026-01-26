/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_append.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:05:46 by juperrin          #+#    #+#             */
/*   Updated: 2026/01/26 13:35:05 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	lst_append(t_list *node, char c)
{
	char	*clean_char;
	char	*new_str;

	if (NULL == node)
		return ;
	clean_char = malloc(sizeof(char) * 2);
	if (!clean_char)
		return ; //ADD FREE FOR LEXER ETC.
	clean_char[0] = c;
	clean_char[1] = '\0';
	if (!node->data)
		node->data = clean_char;
	else
	{
		new_str = ft_strjoin(node->data, clean_char);
		free(node->data);
		node->data = new_str;
	}
}
