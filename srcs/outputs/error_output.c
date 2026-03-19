/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 10:23:31 by juperrin          #+#    #+#             */
/*   Updated: 2026/03/19 14:33:42 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_status	error_output(const char *arg, int error)
{
	const char	*error_msgs[] = {
		"success", "failure", "bad argument", "overflow", "underflow",
		"allocation failure", "execve failure", "pipe failure", "fork failure",
		"dup failure", "open failure", "No such file or directory",
		"Permission denied", "command not found",
		"maximum here-document count exceeded",
	};

	if (NULL != arg)
	{
		if (write(STDERR_FILENO, arg, ft_strlen(arg)) < 0)
			return (FAILURE);
	}
	if (error >= 0)
	{
		if (write(STDERR_FILENO, ": ", 2) < 0)
			return (FAILURE);
		if (write(2, error_msgs[error], ft_strlen(error_msgs[error])) < 0)
			return (FAILURE);
	}
	if (write(STDERR_FILENO, "\n", 1) < 0)
		return (FAILURE);
	return (SUCCESS);
}
