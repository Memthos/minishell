/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 14:35:01 by juperrin          #+#    #+#             */
/*   Updated: 2026/02/20 14:54:06 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
				swap_str(&cpy->key, &cpy->next->key);
				swap_str((char **)&cpy->data, (char **)&cpy->next->data);
			}
			cpy = cpy->next;
		}
		++index;
	}
	return (*dict);	
}
