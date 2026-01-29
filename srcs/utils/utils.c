/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 11:12:55 by juperrin          #+#    #+#             */
/*   Updated: 2026/01/29 11:27:43 by mperrine         ###   ########.fr       */
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

char	*ft_strcpy(char *s)
{
	char	*cpy;
	size_t	size;
	size_t	i;

	if (!s)
		return (NULL);
	size = ft_strlen(s);
	cpy = malloc (sizeof(char) * (size + 1));
	i = 0;
	while (i < size)
	{
		cpy[i] = s[i];
		i++;
	}
	cpy[i] = '\0';
	free(s);
	return (cpy);
}

void	ft_strjoin_sep(char **s1, const char *s2, char sep)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s2)
		return ;
	str = ft_strcpy(*s1);
	if (!str)
		return ;
	*s1 = malloc(sizeof(char) + (ft_strlen(str) + ft_strlen(s2) + (sep != '\0') + 1));
	if (!*s1)
		free(str);
	if (!*s1)
		return ;
	i = 0;
	while (str[i++])
		(*s1)[i - 1] = str[i - 1];
	if (sep != '\0')
		(*s1)[i++] = sep;
	j = 0;
	while (s2[j])
		(*s1)[i++] = s2[j++];
	(*s1)[i] = '\0';
}
