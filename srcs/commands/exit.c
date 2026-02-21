/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 10:02:10 by juperrin          #+#    #+#             */
/*   Updated: 2026/02/21 13:19:20 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_status	cmd_exit(char **args, t_dictionary **env)
{
	int	code;

	(void)env;
	printf("exit\n");
	if (NULL == args || NULL == *args)
		exit(SUCCESS);
	if (!str_is_digit(*args))
	{
		error_output("exit : numeric argument required");
		exit(BAD_ARG);
	}
	if (NULL != *(args + 1))
	{
		error_output("exit : too many arguments");
		exit(FAILURE);
	}
	if (SUCCESS != get_number(*args, &code))
	{
		error_output("exit : numeric argument required");
		exit(BAD_ARG);
	}
	exit(code % 256);
}
