/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 11:12:13 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/28 14:05:09 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_uint	strings_len(const t_strings strs)
{
	t_uint	size;

	if (NULL == strs || NULL == *strs)
		return (0);
	size = 0;
	while (*(strs + size))
		++size;
	return (size);
}

void	strings_free(t_strings strs)
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
