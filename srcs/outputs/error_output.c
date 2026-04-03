/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 10:23:31 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/03 15:46:50 by mperrine         ###   ########.fr       */
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
		"Failed to read directory content"
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

t_status	parser_error_print(const char *arg)
{
	if (!arg)
		return (FAILURE);
	if (write(2, "parser: syntax error near unexpected token `", 44) < 0)
		return (FAILURE);
	if (write(2, arg, ft_strlen(arg)) < 0)
		return (FAILURE);
	if (write(STDERR_FILENO, "'\n", 2) < 0)
		return (FAILURE);
	return (SUCCESS);
}

t_status	amb_red_error_print(const char *arg)
{
	if (!arg)
		return (FAILURE);
	if (write(STDERR_FILENO, "parser: ", 8) < 0)
		return (FAILURE);
	if (write(STDERR_FILENO, arg, ft_strlen(arg)) < 0)
		return (FAILURE);
	if (write(STDERR_FILENO, ": ambiguous redirect\n", 21) < 0)
		return (FAILURE);
	return (SUCCESS);
}

t_status	heredoc_error_print(const char *arg)
{
	if (!arg)
		return (FAILURE);
	if (write(2, "minishell: warning: here-document at line ", 42) < 0)
		return (FAILURE);
	if (write(2, "nbr", 3) < 0)
		return (FAILURE);
	if (write(STDERR_FILENO, " delimited by end-of-file (wanted `", 35) < 0)
		return (FAILURE);
	if (write(2, arg, ft_strlen(arg)) < 0)
		return (FAILURE);
	if (write(2, "')\n", 3) < 0)
		return (FAILURE);
	return (SUCCESS);
}
