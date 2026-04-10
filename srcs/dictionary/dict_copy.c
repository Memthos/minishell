/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_copy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 15:01:29 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/10 14:19:50 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_dictionary	*dict_copy(const t_dictionary *dict)
{
	t_dictionary	*cpy;
	t_dictionary	*head;

	if (NULL == dict)
		return (NULL);
	cpy = malloc(sizeof(t_dictionary));
	head = cpy;
	cpy->key = ft_strdup(dict->key);
	cpy->data = ft_strdup(dict->data);
	while (dict->next)
	{
		cpy->next = malloc(sizeof(t_dictionary));
		if (NULL == cpy->next)
		{
			perror("malloc");
			dict_clear(&cpy);
			return (NULL);
		}
		cpy->next->key = ft_strdup(dict->next->key);
		cpy->next->data = ft_strdup(dict->next->data);
		cpy->next->next = NULL;
		cpy = cpy->next;
		dict = dict->next;
	}
	return (head);
}
