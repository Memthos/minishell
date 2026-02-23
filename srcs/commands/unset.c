/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 09:10:34 by juperrin          #+#    #+#             */
/*   Updated: 2026/02/23 17:44:53 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_status	cmd_unset(char **args, t_shell *shell)
{
	if (NULL == shell)
		return (FAILURE);
	if (NULL == args || NULL == *args)
		return (SUCCESS);
	while (*args)
	{
		dict_remove(&shell->env, *args);
		++args;
	}
	return (SUCCESS);
}
