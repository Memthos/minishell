/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_lst_append.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:40:21 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/09 14:46:41 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_stack	*stack_lst_append(t_stack **stack, void *data)
{
	t_stack	*new;
	t_stack	*cpy;

	if (NULL == stack)
		return (NULL);
	new = stack_lst_new(data);
	if (NULL == *stack)
		return (new);
	cpy = *stack;
	while (cpy->next)
		cpy = cpy->next;
	cpy->next = new;
	return (*stack);
}
