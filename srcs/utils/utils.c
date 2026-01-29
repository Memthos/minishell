/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 11:12:55 by juperrin          #+#    #+#             */
/*   Updated: 2026/01/29 16:24:23 by mperrine         ###   ########.fr       */
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
	return (cpy);
}

void	ft_strjoin_sep(char **s1, const char *s2, char sep)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!*s1 || !s2 || sep == 0)
		return ;
	str = malloc(sizeof(char) + (ft_strlen(*s1) + ft_strlen(s2) + 2));
	if (!str)
		return ;//ERROR
	i = 0;
	while ((*s1)[i])
	{
		str[i] = (*s1)[i];
		i++;
	}
	str[i++] = sep;
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free(*s1);
	*s1 = str;
}
