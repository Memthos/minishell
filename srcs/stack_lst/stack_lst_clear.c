/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_lst_clear.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:36:17 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/09 15:32:00 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	stack_lst_clear(t_stack **stack, void (*del)(void *param))
{
	t_stack	*tmp;

	if (NULL == stack)
		return ;
	while (*stack)
	{
		tmp = (*stack)->next;
		del((*stack)->data);
		(*stack)->data = NULL;
		free(*stack);
		*stack = tmp;
	}
	*stack = NULL;
	return ;
}
