/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:46:53 by juperrin          #+#    #+#             */
/*   Updated: 2026/01/22 13:51:09 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/list.h"
#include "../../includes/definitions.h"

t_uint	lst_size(t_list *head)
{
	t_uint	size;
	
	size = 0;
	while (head)
	{
		++size;
		head = head->next;
	}
	return (size);
}
