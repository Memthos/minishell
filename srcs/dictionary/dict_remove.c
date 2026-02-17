/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_remove.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:16:14 by juperrin          #+#    #+#             */
/*   Updated: 2026/02/17 14:34:40 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_dictionary	*dict_remove(t_dictionary **dict, char *key)
{
	t_dictionary	*current;
	t_dictionary	*rm;

	if (NULL == dict || NULL == *dict || NULL == key)
		return (NULL);
	if (NULL == dict_get(*dict, key))
		return (NULL);
	current = *dict;
	while (current->next->key != key)
		current = current->next;
	rm = current->next;
	current->next = current->next->next;
	free(rm->key);
	free(rm->data);
	free(rm);
	return (*dict);	
}
