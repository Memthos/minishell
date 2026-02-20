/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_size.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 08:08:04 by juperrin          #+#    #+#             */
/*   Updated: 2026/02/20 08:09:04 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_uint	dict_size(t_dictionary *dict)
{
	t_uint	size;

	size = 0;
	while (dict)
	{
		dict = dict->next;
		++size;
	}
	return (size);
}
