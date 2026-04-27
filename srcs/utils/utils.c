/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 11:12:55 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/17 11:35:46 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

void	swap_ptr(void **a, void **b)
{
	void	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	*increment_array(void *array, t_uint count, t_uint size)
{
	void	*new;

	if (NULL == array)
	{
		array = ft_calloc(1, size);
		if (NULL == array)
			return (NULL);
		return (array);
	}
	if (0 == count)
		return (array);
	new = ft_calloc(count + 1, size);
	if (NULL == new)
		return (NULL);
	ft_memcpy(new, array, count * size);
	free(array);
	return (new);
}

t_status	get_number(const t_string s, long *number)
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
		sign = (*(s + index++) % 43) * -1 + 1;
	*number = 0;
	while (ft_isdigit(*(s + index)))
	{
		if ((*number) * sign > (LONG_MAX - ((*(s + index)) - '0')) / 10)
			return (OVERFLOW);
		if ((*number) * sign < (LONG_MIN + ((*(s + index)) - '0')) / 10)
			return (UNDERFLOW);
		*number = *number * 10 + (*(s + index++) - '0');
	}
	*number *= sign;
	if (*(s + index))
		return (BAD_ARG);
	return (SUCCESS);
}

int	ft_close(int *fd)
{
	int	code;

	if (*fd < 0)
		return (SUCCESS);
	code = close(*fd);
	if (SUCCESS != code)
		perror("close");
	*fd = -1;
	return (code);
}

bool	contain_space(t_string str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
			return (true);
		i++;
	}
	return (false);
}
