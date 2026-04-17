/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_lst_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:13:56 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/17 11:20:41 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_uint	stack_lst_size(t_stack *stack)
{
	t_uint	size;

	size = 0;
	while (stack)
	{
		++size;
		stack = stack->next;
	}
	return (size);
}
