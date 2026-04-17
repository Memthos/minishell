/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 14:35:01 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/17 11:35:46 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dictionary	*dict_sort(t_dictionary **dict)
{
	t_uint			size;
	t_uint			index;
	t_dictionary	*cpy;

	if (NULL == dict || NULL == *dict)
		return (NULL);
	size = dict_size(*dict);
	index = 0;
	while (index < size)
	{
		cpy = *dict;
		while (cpy->next)
		{
			if (ft_strcmp(cpy->key, cpy->next->key) > 0)
			{
				swap_ptr((void **)&cpy->key, (void **)&cpy->next->key);
				swap_ptr(&cpy->data, &cpy->next->data);
			}
			cpy = cpy->next;
		}
		++index;
	}
	return (*dict);
}
