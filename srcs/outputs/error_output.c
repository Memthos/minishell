/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 10:23:31 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/28 13:52:42 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_string	get_error(int index)
{
	static const t_string	error_msgs[] = {
		"success", "failure", "bad argument", "too many arguments", "overflow",
		"underflow", "allocation failure", "execve failure", "pipe failure",
		"fork failure",	"dup failure", "open failure", "read failure",
		"No such file or directory", "Permission denied", "command not found",
		"Is a directory", "maximum here-document count exceeded",
		"Failed to read directory content", "numeric argument required",
		"not a valid identifier"
	};

	if (index < 0)
		return ("");
	return (error_msgs[index]);
}

t_status	error_output(const t_string cmd, const t_string arg, int error)
{
	t_status	code;

	code = SUCCESS;
	if (write(STDERR_FILENO, "minishell: ", 11) < 0)
		code = FAILURE;
	if (NULL != cmd)
	{
		if (write(STDERR_FILENO, cmd, ft_strlen(cmd)) < 0)
			code = FAILURE;
		if (write(STDERR_FILENO, ": ", 2) < 0)
			code = FAILURE;
	}
	if (NULL != arg)
	{
		if (write(STDERR_FILENO, arg, ft_strlen(arg)) < 0)
			code = FAILURE;
		if (error >= 0)
			if (write(STDERR_FILENO, ": ", 2) < 0)
				code = FAILURE;
	}
	if (write(2, get_error(error), ft_strlen(get_error(error))) < 0)
		code = FAILURE;
	if (write(STDERR_FILENO, "\n", 1) < 0)
		code = FAILURE;
	return (code);
}

t_status	parser_error_print(const t_string arg)
{
	if (!arg)
		return (FAILURE);
	if (write(2, "minishell: syntax error near unexpected token `", 47) < 0)
		return (FAILURE);
	if (write(STDERR_FILENO, arg, ft_strlen(arg)) < 0)
		return (FAILURE);
	if (write(STDERR_FILENO, "'\n", 2) < 0)
		return (FAILURE);
	return (SUCCESS);
}

t_status	amb_red_error_print(const t_string arg)
{
	if (!arg)
		return (FAILURE);
	if (write(STDERR_FILENO, "minishell: ", 11) < 0)
		return (FAILURE);
	if (write(STDERR_FILENO, arg, ft_strlen(arg)) < 0)
		return (FAILURE);
	if (write(STDERR_FILENO, ": ambiguous redirect\n", 21) < 0)
		return (FAILURE);
	return (SUCCESS);
}

t_status	heredoc_error_print(const t_string arg)
{
	if (!arg)
		return (FAILURE);
	if (write(2, "minishell: warning: here-document", 33) < 0)
		return (FAILURE);
	if (write(STDERR_FILENO, " delimited by end-of-file (wanted `", 35) < 0)
		return (FAILURE);
	if (write(2, arg, ft_strlen(arg)) < 0)
		return (FAILURE);
	if (write(2, "')\n", 3) < 0)
		return (FAILURE);
	return (SUCCESS);
}
