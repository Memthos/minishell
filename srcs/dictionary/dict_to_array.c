/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_to_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 08:06:45 by juperrin          #+#    #+#             */
/*   Updated: 2026/02/20 08:21:11 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**dict_to_array(t_dictionary *dict, char sep)
{
	t_uint	index;
	t_uint	size;
	char	**arr;

	if (NULL == dict || '\0' == sep)
		return (NULL);
	size = dict_size(dict);
	arr = (char **)malloc(sizeof(char *) * (size + 1));
	if (NULL == arr)
		return (NULL);
	index = 0;
	while (dict && index < size)
	{
		arr[index] = ft_strjoin_sep(dict->key, dict->data, sep);
		if (NULL == arr[index])
		{
			free_strings(arr);
			return (NULL);
		}
		dict = dict->next;
		++index;
	}
	arr[index] = NULL;
	return (arr);
}
