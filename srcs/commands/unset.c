/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 09:10:34 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/17 11:06:18 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_status	cmd_unset(t_strings args, t_shell *shell)
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
