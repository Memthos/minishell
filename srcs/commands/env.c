/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 12:51:11 by juperrin          #+#    #+#             */
/*   Updated: 2026/02/24 16:23:47 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_status	cmd_env(char **args, t_shell *shell)
{
	if (NULL == shell)
		return (FAILURE);
	if (NULL != args[1])
		return (SUCCESS);
	dict_display(shell->env, "", "=");
	return (SUCCESS);
}
