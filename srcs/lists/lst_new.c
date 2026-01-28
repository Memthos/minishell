/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 11:09:00 by juperrin          #+#    #+#             */
/*   Updated: 2026/01/28 11:05:29 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*lst_new(char *data, t_token token, size_t parenth_dpt)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (NULL == new)
		return (NULL); //ADD FREE FOR LEXER ETC.
	new->data = data;
	new->token = token;
	new->parenth_dpt = parenth_dpt;
	new->next = NULL;
	return (new);
}
