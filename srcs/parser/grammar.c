/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 13:04:22 by mperrine          #+#    #+#             */
/*   Updated: 2026/01/27 13:49:49 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_io_number_t(t_list *lst)
{
	size_t	i;

	while (lst)
	{
		i = 0;
		while (lst->data[i] && lst->data[i] >= '0' && lst->data[i] <= '9')
			i++;
		if (i == ft_strlen(lst->data))
			lst->token = IO_NUMBER;
		lst = lst->next;
	}
}
