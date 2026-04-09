/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_lst_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:30:37 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/09 14:44:02 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

t_stack	*stack_lst_new(void	*data)
{
	t_stack	*new;

	new = malloc(sizeof(t_stack));
	if (NULL == new)
	{
		perror("malloc");
		return (NULL);
	}
	new->data = data;
	new->next = NULL;
	return (new);
}
