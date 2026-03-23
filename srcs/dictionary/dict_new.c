/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 10:08:18 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/21 15:39:04 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_dictionary	*dict_new(char *key, void *data)
{
	t_dictionary	*dict;

	if (NULL == key)
		return (NULL);
	dict = (t_dictionary *)malloc(sizeof(t_dictionary));
	if (NULL == dict)
	{
		free(key);
		free(data);
		perror("malloc");
		return (NULL);
	}
	dict->key = key;
	dict->data = data;
	dict->next = NULL;
	return (dict);
}
