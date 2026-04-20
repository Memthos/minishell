/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:18:11 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/17 11:35:46 by juperrin         ###   ########.fr       */
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

t_pipe	*pipe_get(t_shell *shell, t_side side)
{
	t_stack	*cpy;
	t_pipe	*last;

	if (NULL == shell)
		return (NULL);
	last = NULL;
	cpy = shell->pipe_stack;
	while (cpy)
	{
		if (((t_pipe *)cpy->data)->side == side)
			last = (t_pipe *)cpy->data;
		cpy = cpy->next;
	}
	return (last);
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
