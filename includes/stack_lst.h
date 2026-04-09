/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_lst.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:29:08 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/09 15:36:58 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_LST_H
# define STACK_LST_H

typedef struct s_stack
{
	void			*data;
	struct s_stack	*next;
}	t_stack;

t_stack	*stack_lst_new(void *data);

t_stack	*stack_lst_append(t_stack **stack, void *data);

t_stack	*stack_lst_pop(t_stack **stack, void (*del)(void *param));

void	stack_lst_clear(t_stack **stack, void (*del)(void *param));

t_uint	stack_lst_size(t_stack *stack);

#endif