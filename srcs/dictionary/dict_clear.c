/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 10:07:53 by mperrine          #+#    #+#             */
/*   Updated: 2026/02/17 14:02:58 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
