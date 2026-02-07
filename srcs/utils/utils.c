/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 11:12:55 by juperrin          #+#    #+#             */
/*   Updated: 2026/02/07 19:49:51 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_status	get_number(const char *s, int *number)
{
	int		sign;
	t_uint	index;

	if (NULL == s || NULL == number)
		return (FAILURE);
	index = 0;
	while ((*(s + index) >= 9 && *(s + index) <= 13) || ' ' == *(s + index))
		++index;
	sign = 1;
	if (*(s + index) == '-' || *(s + index) == '+')
	{
		if (*(s + index++) == '-')
			sign = -1;
	}
	*number = 0;
	while (ft_isdigit(*(s + index)))
	{
		if (((long)(*number) *10 + (*(s + index) - '0')) * sign > INT32_MAX)
			return (OVERFLOW);
		if (((long)(*number) *10 + (*(s + index) - '0')) * sign < INT32_MIN)
			return (UNDERFLOW);
		*number = *number * 10 + (*(s + index++) - '0');
	}
	*number *= sign;
	return (SUCCESS);
}
