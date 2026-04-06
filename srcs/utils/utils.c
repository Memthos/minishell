/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 11:12:55 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/06 21:15:33 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//NOT USED
t_uint	count_words(const char *str, const char *set)
{
	t_uint	count;
	t_uint	index;
	t_uint8	add;

	count = 0;
	add = 1;
	index = 0;
	while (*(str + index))
	{
		if (strchr(set, *(str + index)))
			add = 1;
		else if (add)
		{
			++count;
			add = 0;
		}
		++index;
	}
	return (count);
}
