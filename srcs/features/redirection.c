/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 21:04:53 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/20 21:22:09 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	redirect_input(int *fd)
{
	if (*fd < 0)
		return (SUCCESS);
	if (-1 == dup2(*fd, STDIN_FILENO))
	{
		perror("dup2");
		ft_close(fd);
		return (DUP_FAILURE);
	}
	ft_close(fd);
	return (SUCCESS);
}

t_status	redirect_output(int *fd)
{
	if (*fd < 0)
		return (SUCCESS);
	if (-1 == dup2(*fd, STDOUT_FILENO))
	{
		perror("dup2");
		ft_close(fd);
		return (DUP_FAILURE);
	}
	ft_close(fd);
	return (SUCCESS);
}
