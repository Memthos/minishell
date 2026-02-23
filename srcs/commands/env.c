/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 12:51:11 by juperrin          #+#    #+#             */
/*   Updated: 2026/02/23 17:45:07 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_status	cmd_env(char **args, t_shell *shell)
{
	if (NULL == shell)
		return (FAILURE);
	if (NULL != args && NULL != *args)
		return (SUCCESS);
	dict_display(shell->env, "", "=");
	return (SUCCESS);
}
