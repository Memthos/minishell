/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 10:38:34 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/17 11:06:18 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	is_dash_n(const t_string s)
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

t_status	cmd_echo(t_strings args, t_shell *shell)
{
	t_status	code;
	bool		line_break;

	(void)shell;
	code = SUCCESS;
	line_break = true;
	while (is_dash_n(*(args + 1)))
	{
		line_break = false;
		++args;
	}
	while (*(args + 1))
	{
		if (write(1, *(args + 1), ft_strlen(*(args + 1))) < 0)
			code = FAILURE;
		if (*(args + 1 + 1))
			if (write(STDOUT_FILENO, " ", 1) < 0)
				code = FAILURE;
		++args;
	}
	if (line_break)
		if (write(STDOUT_FILENO, "\n", 1) < 0)
			code = FAILURE;
	return (code);
}
