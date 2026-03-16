/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 08:48:38 by juperrin          #+#    #+#             */
/*   Updated: 2026/03/16 16:18:44 by juperrin         ###   ########.fr       */
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
	if (ENOENT == errno)
	{
		if (ft_strchr(*args, '/'))
			perror(*args);
		else
		{
			error_output(*args);
			error_output(": command not found\n");
		}
	}
	free_strings(envp);
	return (127);
}
