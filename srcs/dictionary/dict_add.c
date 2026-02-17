/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 17:43:38 by mperrine          #+#    #+#             */
/*   Updated: 2026/02/17 14:43:36 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_dictionary	*dict_add(t_dictionary **dict, char *key, void *data)
{
	t_dictionary	*cpy;
	t_dictionary	*new;

	if (NULL == dict)
		return (NULL);
	if (NULL != dict_get(*dict, key))
		return (NULL);
	cpy = *dict;
	while (cpy->next)
		cpy = cpy->next;
	new = dict_new(key, data);
	if (NULL == new)
		return (NULL);
	cpy->next = new;
	return (*dict);
}
