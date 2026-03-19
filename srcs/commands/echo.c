/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 10:38:34 by juperrin          #+#    #+#             */
/*   Updated: 2026/03/19 10:30:31 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	is_dash_n(const char *s)
{
	t_uint	index;

	if (NULL == s)
		return (false);
	if (*s != '-')
		return (false);
	index = 1;
	while (*(s + index))
	{
		if (*(s + index) != 'n')
			return (false);
		++index;
	}
	if (1 == index)
		return (false);
	return (true);
}

t_status	cmd_echo(char **args, t_shell *shell)
{
	t_uint	index;
	bool	line_break;

	(void)shell;
	if (NULL == args[1])
	{
		write(STDOUT_FILENO, "\n", 1);
		return (SUCCESS);
	}
	line_break = true;
	index = 1;
	while (is_dash_n(*(args + index)))
	{
		line_break = false;
		++index;
	}
	while (*(args + index))
	{
		write(STDOUT_FILENO, *(args + index), ft_strlen(*(args + index)));
		if (*(args + index + 1))
			write(STDOUT_FILENO, " ", 1);
		++index;
	}
	if (line_break)
		write(STDOUT_FILENO, "\n", 1);
	return (SUCCESS);
}
