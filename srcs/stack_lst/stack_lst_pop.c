/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_lst_pop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:46:51 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/17 11:35:46 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_stack	*stack_lst_pop(t_stack **stack, void (*del)(void *param))
{
	t_stack	*cpy;

	if (NULL == stack || NULL == *stack)
		return (NULL);
	if (NULL == (*stack)->next)
	{
		stack_lst_clear(stack, del);
		return (NULL);
	}
	cpy = *stack;
	while (cpy->next->next)
		cpy = cpy->next;
	del(cpy->next->data);
	cpy->next->data = NULL;
	free(cpy->next);
	cpy->next = NULL;
	return (*stack);
}
