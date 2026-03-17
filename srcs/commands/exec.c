/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 08:48:38 by juperrin          #+#    #+#             */
/*   Updated: 2026/03/17 14:03:04 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_status	cmd_exec(char **args, t_shell *shell)
{
	char	*save;
	char	*tmp;
	char	**envp;

	if (NULL == args || NULL == *args)
		return (FAILURE);
	save = *args;
	envp = dict_to_array(shell->env, '=');
	if ('/' != **args && dict_get(shell->env, "PATH"))
	{
		tmp = ft_strjoin("/bin/", *args);
		if (NULL == tmp)
			perror("malloc");
		else
			*args = tmp;
	}
	execve(*args, args, envp);
	if (ENOENT == errno)
	{
		if (ft_strchr(*args, '/') || NULL == dict_get(shell->env, "PATH"))
			perror(save);
		else
		{
			error_output(save);
			error_output(": command not found\n");
		}
	}
	if (*args != save)
		free(*args);
	*args = save;
	free_strings(envp);
	return (127);
}
