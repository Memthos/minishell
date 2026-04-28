/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 12:51:11 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/28 13:13:26 by mperrine         ###   ########.fr       */
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
		{
			write(1, cpy->key, ft_strlen(cpy->key));
			write(1, "=", 1);
			write(1, (t_string)cpy->data, ft_strlen((t_string)cpy->data));
			write(1, "\n", 1);
		}
		cpy = cpy->next;
	}
	return (SUCCESS);
}
