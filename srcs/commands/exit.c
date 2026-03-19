/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 10:02:10 by juperrin          #+#    #+#             */
/*   Updated: 2026/03/19 10:47:35 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_status	cmd_exit(char **args, t_shell *shell)
{
	int	code;

	if (!shell->pipes.pipe_depth)
		error_output("exit\n");
	if (NULL == args[1])
	{
		destroy_shell(shell);
		exit(SUCCESS);
	}
	if (NULL != args[2])
	{
		error_output("exit : too many arguments\n");
		destroy_shell(shell);
		exit(FAILURE);
	}
	if (SUCCESS != get_number(args[1], &code))
	{
		error_output("exit : numeric argument required\n");
		destroy_shell(shell);
		exit(BAD_ARG);
	}
	destroy_shell(shell);
	exit(code & 0xff);
}
