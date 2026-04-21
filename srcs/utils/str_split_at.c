/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_split_at.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 22:33:35 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/21 22:46:34 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_strings	split_assign(t_strings split, const t_string str, t_uint n)
{
	*split = (t_string)malloc(sizeof(char) * (n + 1));
	if (NULL == *split)
	{
		free(split);
		return (NULL);
	}
	ft_strlcpy(*split, str, n + 1);
	if ('\0' == *(str + n))
	{
		split[1] = NULL;
		return (split);
	}
	split[1] = malloc(sizeof(char) * (ft_strlen(str) - n));
	if (NULL == split[1])
	{
		free(*split);
		free(split);
		return (NULL);
	}
	ft_strlcpy(split[1], str + n + 1, ft_strlen(str) - n);
	return (split);
}

t_strings	str_split_at(const t_string str, const char c)
{
	t_strings	split;
	t_uint		index;

	if (NULL == str)
		return (NULL);
	split = (t_strings)malloc(sizeof(t_string) * 2);
	if (NULL == split)
		return (NULL);
	index = 0;
	while (*(str + index) && *(str + index) != c)
		++index;
	if (NULL == split_assign(split, str, index))
		return (NULL);
	return (split);
}
