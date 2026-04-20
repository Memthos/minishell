/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_copy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 15:01:29 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/20 14:23:12 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_dictionary	*copy_next(t_dictionary *dst, const t_dictionary *src)
{
	dst->next = dict_new(ft_strdup(src->next->key),
			ft_strdup((t_string)src->next->data));
	if (0 == dst->next->key || (0 == dst->next->data && 0 != src->next->data))
	{
		perror("malloc");
		return (NULL);
	}
	return (dst);
}

t_dictionary	*dict_copy(const t_dictionary *dict)
{
	t_dictionary	*cpy;
	t_dictionary	*head;

	if (NULL == dict)
		return (NULL);
	cpy = dict_new(ft_strdup(dict->key), ft_strdup((t_string)dict->data));
	if (NULL == cpy->key || (NULL == cpy->data && NULL != dict->data))
	{
		perror("malloc");
		dict_clear(&head);
		return (NULL);
	}
	head = cpy;
	while (dict->next)
	{
		if (NULL == copy_next(cpy, dict))
		{
			dict_clear(&head);
			return (NULL);
		}
		cpy->next->next = NULL;
		cpy = cpy->next;
		dict = dict->next;
	}
	return (head);
}
