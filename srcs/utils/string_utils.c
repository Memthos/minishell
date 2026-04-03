/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 09:42:06 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/03 21:15:53 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	str_is_digit(char *str)
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

bool	str_is_empty(char *str)
{
	if (NULL == str || 0 == str[0])
		return (true);
	return (false);
}

int	contain_space(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}
