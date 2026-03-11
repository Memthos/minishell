/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 10:02:10 by juperrin          #+#    #+#             */
/*   Updated: 2026/03/11 16:42:38 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_status	cmd_exit(char **args, t_shell *shell)
{
	int	code;

	printf("exit\n");
	if (NULL == args[1])
	{
		destroy(shell);
		exit(SUCCESS);
	}
	if (!str_is_digit(args[1]))
	{
		error_output("exit : numeric argument required");
		destroy(shell);
		exit(BAD_ARG);
	}
	if (NULL != args[2])
	{
		error_output("exit : too many arguments");
		destroy(shell);
		exit(FAILURE);
	}
	if (SUCCESS != get_number(args[1], &code))
	{
		error_output("exit : numeric argument required");
		destroy(shell);
		exit(BAD_ARG);
	}
	destroy(shell);
	exit(code % 256);
}
