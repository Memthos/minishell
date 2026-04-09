/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_lst_pop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:46:51 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/09 14:50:54 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_stack	*stack_lst_pop(t_stack **stack)
{
	t_stack	*cpy;

	if (NULL == stack || NULL == *stack)
		return (NULL);
	if (NULL == (*stack)->next)
	{
		stack_lst_clear(stack);
		return (NULL);
	}
	cpy = *stack;
	while (cpy->next->next)
		cpy = cpy->next;
	free((*stack)->next->data);
	free((*stack)->next);
	(*stack)->next = NULL;
	return (*stack);
}
