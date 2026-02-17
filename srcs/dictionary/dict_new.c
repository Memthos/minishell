/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 10:08:18 by mperrine          #+#    #+#             */
/*   Updated: 2026/02/17 13:59:21 by juperrin         ###   ########.fr       */
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
		return (NULL);
	dict->key = key;
	dict->data = data;
	dict->next = NULL;
	return (dict);
}
