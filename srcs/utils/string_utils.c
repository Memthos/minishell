/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 11:12:13 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/17 11:13:26 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	str_is_digit(t_string str)
{
	if (NULL == str)
		return (false);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		++str;
	}
	return (true);
}

t_strings	split_at(const t_string str, const char c)
{
	t_strings	split;
	t_uint		index;

	if (!ft_strchr(str, c))
		return (NULL);
	split = (t_strings)malloc(sizeof(t_string) * 2);
	if (NULL == split)
		return (NULL);
	index = 0;
	while (*(str + index) != c)
		++index;
	*split = (t_string)malloc(sizeof(char) * (index + 1));
	*(split + 1) = (t_string)malloc(sizeof(char) * (ft_strlen(str) - index));
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

t_uint	t_strings_size(const t_strings strs)
{
	t_uint	size;

	if (NULL == strs || NULL == *strs)
		return (0);
	size = 0;
	while (*(strs + size))
		++size;
	return (size);
}

void	free_t_strings(t_strings strs)
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

bool	str_is_empty(t_string str)
{
	if (NULL == str || 0 == str[0])
		return (true);
	return (false);
}
