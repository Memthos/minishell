/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 15:49:18 by juperrin          #+#    #+#             */
/*   Updated: 2026/01/27 15:52:17 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*The way that the command is passed as an argument will be changed, but the
logic stay the same*/
t_status	exec(const char *command)
{
	pid_t	id;
	char 	**cmd;
	int		code;

	id = fork();
	if (NULL == command || -1 == id)
		return (FAILURE);
	if (0 == id)
	{
		cmd = split(command, "\t ");
		if (NULL == cmd)
			return (FAILURE);
		execve(*cmd, cmd, NULL);
		free_strings(cmd);
		exit(FAILURE);
	}
	wait(&code);
	if (WIFEXITED(code))
	{
		code = WEXITSTATUS(code);
		return (code);
	}
	return (SUCCESS);	
}
