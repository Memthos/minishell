/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 09:10:34 by juperrin          #+#    #+#             */
/*   Updated: 2026/02/21 11:31:06 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_status	cmd_unset(char **args, t_dictionary **env)
{
	if (NULL == env || NULL == *env)
		return (FAILURE);
	if (NULL == args || NULL == *args)
		return (SUCCESS);
	while (*args)
	{
		dict_remove(env, *args);
		++args;
	}
	return (SUCCESS);
}
