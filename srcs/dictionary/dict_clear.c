/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 10:07:53 by mperrine          #+#    #+#             */
/*   Updated: 2026/04/17 11:35:46 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dict_clear(t_dictionary **dict)
{
	t_dictionary	*tmp;

	if (NULL == dict)
		return ;
	while (*dict)
	{
		tmp = (*dict)->next;
		free((*dict)->key);
		free((*dict)->data);
		free(*dict);
		*dict = tmp;
	}
	return ;
}
