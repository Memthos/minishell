/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 14:48:54 by juperrin          #+#    #+#             */
/*   Updated: 2026/02/12 07:58:12 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec(char *command, int input_fd, int output_fd)
{
	char	**args;
	int		code;

	if (NULL == command)
		return (FAILURE);
	if (-1 != output_fd)
	{
		if (-1 == dup2(output_fd, STDOUT_FILENO))
		{
			close(output_fd);
			return (DUP_FAILURE);
		}
		close(output_fd);
	}
	if (-1 != input_fd)
	{
		if (-1 == dup2(input_fd, STDIN_FILENO))
		{
			close(input_fd);
			return (DUP_FAILURE);
		}
		close(input_fd);
	}
	args = ft_split(command, ' ');
	if (NULL == args)
		return (FAILURE);
	code = execve(*args, args, NULL);
	free_strings(args);
	return (code);
}
