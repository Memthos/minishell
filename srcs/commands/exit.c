/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 10:02:10 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/25 14:25:11 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	cmd_exit(t_strings args, t_shell *shell)
{
	int	code;

	if (0 == shell->pipe_depth)
		write(STDERR_FILENO, "exit\n", 5);
	if (NULL == args[1])
	{
		destroy_shell(shell, false);
		exit(SUCCESS);
	}
	if (SUCCESS != get_number(args[1], &code))
	{
		error_output("exit", args[1], NUM_ARG_REQUIRED);
		destroy_shell(shell, false);
		exit(BAD_ARG);
	}
	if (NULL != args[2])
	{
		error_output("exit", NULL, TOO_MUCH_ARG);
		shell->exitno = FAILURE;
		return (shell->exitno);
	}
	destroy_shell(shell, false);
	exit(code & 0xff);
}
