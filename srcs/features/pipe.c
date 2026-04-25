/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:18:11 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/25 14:14:25 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipe	*pipe_new(void)
{
	t_pipe	*new;

	new = malloc(sizeof(t_pipe));
	if (NULL == new)
	{
		perror("malloc");
		return (NULL);
	}
	new->side = LEFT;
	if (-1 == pipe(new->pipe))
	{
		perror("pipe");
		free(new);
		return (NULL);
	}
	return (new);
}

void	pipe_close(t_pipe *pipe)
{
	if (NULL == pipe)
		return ;
	ft_close(&pipe->pipe[0]);
	ft_close(&pipe->pipe[1]);
	free(pipe);
	return ;
}
