/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_lst_clear.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:36:17 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/09 14:40:06 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	stack_lst_clear(t_stack **stack)
{
	t_stack	*tmp;

	if (NULL == stack)
		return ;
	while (*stack)
	{
		tmp = (*stack)->next;
		free((*stack)->data);
		free(*stack);
		*stack = tmp;
	}
	return ;
}
