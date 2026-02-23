/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 10:02:10 by juperrin          #+#    #+#             */
/*   Updated: 2026/02/23 17:20:12 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_status	cmd_exit(char **args, t_dictionary **env)
{
	int	code;

	(void)env;
	printf("exit\n");
	if (NULL == args || NULL == *args)
		return (SUCCESS);
	if (!str_is_digit(*args))
	{
		error_output("exit : numeric argument required");
		return (BAD_ARG);
	}
	if (NULL != *(args + 1))
	{
		error_output("exit : too many arguments");
		return (FAILURE);
	}
	if (SUCCESS != get_number(*args, &code))
	{
		error_output("exit : numeric argument required");
		return (BAD_ARG);
	}
	return (code % 256);
}
