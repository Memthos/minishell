/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 11:12:55 by juperrin          #+#    #+#             */
/*   Updated: 2026/03/20 12:55:59 by mperrine         ###   ########.fr       */
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
		sign = (*(s + index++) % 43) * -1 + 1;
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
	if (*(s + index))
		return (BAD_ARG);
	return (SUCCESS);
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

bool	check_var_name(char *name)
{
	if (NULL == name)
		return (false);
	if (!ft_isalpha(*name))
		return (false);
	while (*name)
	{
		if (!ft_isalnum(*name) && *name != '_')
			return (false);
		++name;
	}
	return (true);
}

void	swap_str(char **a, char **b)
{
	char	*tmp;

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

bool	check_path(t_shell *shell)
{
	t_dictionary	*e;

	if (NULL == shell || NULL == shell->env)
		return (false);
	e = dict_get(shell->env, "PATH");
	if (NULL == e)
		return (false);
	if (*((char *)e->data) == '\0')
		return (false);
	return (true);
}
