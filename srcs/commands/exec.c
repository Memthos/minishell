/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 15:49:18 by juperrin          #+#    #+#             */
/*   Updated: 2026/01/27 18:21:12 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*The way that the command is passed as an argument will be changed, but the
logic stay the same*/
t_status	exec(const char *command, int redirect)
{
	pid_t	id;
	char 	**cmd;
	int		code;

	if (NULL == command || redirect < 0)
		return (FAILURE);
	id = fork();
	if (-1 == id)
		return (FAILURE);
	if (0 == id)
	{
		if (-1 == dup2(redirect, STDOUT_FILENO))
			exit(FAILURE);
		if (redirect != STDOUT_FILENO)
			close(redirect);
		cmd = split(command, "\t ");
		if (NULL == cmd)
			return (FAILURE);
		execve(*cmd, cmd, NULL);
		free_strings(cmd);
		exit(FAILURE);
	}
	wait(&code);
	code = (((code & 0x7f) == 0) & 0xff00) >> 8;
	return (code);
}
