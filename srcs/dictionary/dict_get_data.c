/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_get_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:06:10 by juperrin          #+#    #+#             */
/*   Updated: 2026/03/16 15:54:50 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*dict_get_data(t_dictionary *dict, char *key)
{
	t_dictionary	*node;

	node = dict_get(dict, key);
	if (!node)
		return (NULL);
	return (dict->data);
}
