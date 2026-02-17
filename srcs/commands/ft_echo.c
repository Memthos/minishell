/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 10:38:34 by juperrin          #+#    #+#             */
/*   Updated: 2026/02/17 14:38:05 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_status	ft_echo(char *msg, t_uint8 line_break)
{
	t_status	code;

	if (NULL == msg)
	{
		if (line_break && -1 == write(1, "\n", 1))
			perror("Failed to write on stdout");
		return (SUCCESS);
	}
	code = SUCCESS;
	if (-1 == write(1, msg, ft_strlen(msg)))
	{
		perror("Failed to write on stdout");
		code = FAILURE;
	}
	if (line_break && -1 == write(1, "\n", 1))
	{
		perror("Failed to write on stdout");
		code = FAILURE;
	}
	return (code);
}
