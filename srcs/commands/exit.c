/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 10:02:10 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/07 15:12:08 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_status	cmd_exit(char **args, t_shell *shell)
{
	int	code;

	if (!shell->pipes.pipe_depth)
		write(STDERR_FILENO, "exit\n", 5);
	if (NULL == args[1])
	{
		destroy_shell(shell);
		exit(SUCCESS);
	}
	if (SUCCESS != get_number(args[1], &code))
	{
		error_output("exit", args[1], NUM_ARG_REQUIRED);
		destroy_shell(shell);
		exit(BAD_ARG);
	}
	if (NULL != args[2])
	{
		error_output("exit", NULL, TOO_MUCH_ARG);
		shell->exitno = FAILURE;
		return (shell->exitno);
	}
	destroy_shell(shell);
	exit(code & 0xff);
}
