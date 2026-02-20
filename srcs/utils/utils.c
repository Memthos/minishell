/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 11:12:55 by juperrin          #+#    #+#             */
/*   Updated: 2026/02/20 17:00:34 by juperrin         ###   ########.fr       */
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

char	**split_at(const char *str, const char c)
{
	char	**split;
	t_uint	index;

	if (!ft_strchr(str, c))
		return (NULL);
	split = (char **)malloc(sizeof(char *) * 2);
	if (NULL == split)
		return (NULL);
	index = 0;
	while (*(str + index) != c)
		++index;
	*split = (char *)malloc(sizeof(char) * (index + 1));
	*(split + 1) = (char *)malloc(sizeof(char) * (ft_strlen(str) - index));
	if (NULL == *split || NULL == *(split + 1))
	{
		free(*split);
		free(*(split + 1));
		free(split);
		return (NULL);
	}
	ft_strlcpy(*split, str, index + 1);
	ft_strlcpy(*(split + 1), str + index + 1, ft_strlen(str) - index);
	return (split);
}

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

void	free_strings(char **strs)
{
	t_uint	index;

	if (NULL == strs)
		return ;
	index = 0;
	while (*(strs + index))
	{
		free(*(strs + index));
		++index;
	}
	free(strs);
	return ;
}

void	swap_str(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
