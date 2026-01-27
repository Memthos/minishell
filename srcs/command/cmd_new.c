/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 11:09:00 by juperrin          #+#    #+#             */
/*   Updated: 2026/01/26 13:35:13 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*lst_new(char *data, t_token token)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (NULL == new)
		return (NULL); //ADD FREE FOR LEXER ETC.
	new->data = data;
	new->token = token;
	new->next = NULL;
	return (new);
}
