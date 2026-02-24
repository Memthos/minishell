/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 10:38:34 by juperrin          #+#    #+#             */
/*   Updated: 2026/02/24 16:22:26 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_status	cmd_echo(char **args, t_shell *shell)
{
	t_uint	index;

	(void)shell;
	if (NULL == args[1])
	{
		write(STDOUT_FILENO, "\n", 1);
		return (SUCCESS);
	}
	index = 1;
	while (*(args + index) && !strcmp(*(args + index), "-n"))
		++index;
	while (*(args + index))
	{
		write(STDOUT_FILENO, *(args + index), ft_strlen(*(args + index)));
		if (*(args + index + 1))
			write(STDOUT_FILENO, " ", 1);
		++index;
	}
	if (ft_strcmp(args[1], "-n"))
		write(STDOUT_FILENO, "\n", 1);
	return (SUCCESS);
}
