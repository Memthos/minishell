/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 14:13:45 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/01 15:32:33 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_status	init_pipes(t_pipe_logic *pipes)
{
	if (NULL == pipes)
		return (FAILURE);
	pipes->redirect_input = false;
	pipes->redirect_output = false;
	pipes->left_pipe[0] = -1;
	pipes->left_pipe[1] = -1;
	pipes->left_cmp_pipe[0] = -1;
	pipes->left_cmp_pipe[1] = -1;
	pipes->right_pipe[0] = -1;
	pipes->right_pipe[1] = -1;
	pipes->right_cmp_pipe[0] = -1;
	pipes->right_cmp_pipe[1] = -1;
	pipes->pipe_index = 0;
	pipes->pipe_depth = 0;
	return (SUCCESS);
}

int	*get_cur_pipe(t_pipe_logic *pipes, bool input, bool cmp_pipe)
{
	if (NULL == pipes)
		return (NULL);
	if (cmp_pipe)
	{
		if (pipes->cmp_pipe_index % 2 - input)
			return (pipes->right_cmp_pipe);
		else
			return (pipes->left_cmp_pipe);
	}
	if (pipes->pipe_index % 2 - input)
		return (pipes->right_pipe);
	else
		return (pipes->left_pipe);
}
