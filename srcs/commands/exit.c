/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 10:02:10 by juperrin          #+#    #+#             */
/*   Updated: 2026/02/24 16:24:39 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_status	cmd_exit(char **args, t_shell *shell)
{
	int	code;

	printf("exit\n");
	destroy(shell);
	if (NULL == args[1])
		exit(SUCCESS);
	if (!str_is_digit(args[1]))
	{
		error_output("exit : numeric argument required");
		exit(BAD_ARG);
	}
	if (NULL != args[2])
	{
		error_output("exit : too many arguments");
		exit(FAILURE);
	}
	if (SUCCESS != get_number(args[1], &code))
	{
		error_output("exit : numeric argument required");
		exit(BAD_ARG);
	}
	exit(code % 256);
}
