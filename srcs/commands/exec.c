/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 08:48:38 by juperrin          #+#    #+#             */
/*   Updated: 2026/02/23 17:45:14 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_status	cmd_exec(char **args, t_shell *shell)
{
	char	**envp;

	if (NULL == args || NULL == *args)
		return (FAILURE);
	envp = dict_to_array(shell->env, '=');
	execve(*args, args, envp);
	free_strings(envp);
	return (FAILURE);
}
