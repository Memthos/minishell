/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_update.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 15:05:25 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/17 11:35:46 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dictionary	*dict_update(t_dictionary *dict, t_string key, void *data)
{
	t_dictionary	*update;

	if (NULL == dict || NULL == key)
		return (NULL);
	update = dict_get(dict, key);
	if (NULL == update)
		return (NULL);
	free(update->data);
	update->data = data;
	return (dict);
}
