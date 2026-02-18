/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_get.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:06:10 by juperrin          #+#    #+#             */
/*   Updated: 2026/02/18 11:48:05 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_dictionary	*dict_get(t_dictionary *dict, char *key)
{
	if (NULL == dict || NULL == key)
		return (NULL);
	while (dict && ft_strcmp(key, dict->key))
		dict = dict->next;
	return (dict);
}
