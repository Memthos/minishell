/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_get_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:06:10 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/23 01:47:44 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*dict_get_data(t_dictionary *dict, t_string key)
{
	t_dictionary	*node;

	node = dict_get(dict, key);
	if (!node)
		return (NULL);
	return (node->data);
}
