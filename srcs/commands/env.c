/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 12:51:11 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/27 10:25:29 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	cmd_env(t_strings args, t_shell *shell)
{
	t_dictionary	*cpy;

	if (NULL == shell)
		return (FAILURE);
	if (NULL != args[1])
	{
		error_output("env", NULL, TOO_MUCH_ARG);
		return (BAD_ARG);
	}
	cpy = shell->env;
	while (cpy)
	{
		if (NULL != cpy->data)
			printf("%s=%s\n", cpy->key, (t_string)cpy->data);
		cpy = cpy->next;
	}
	return (SUCCESS);
}
