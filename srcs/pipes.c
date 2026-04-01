/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 14:13:45 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/01 13:32:49 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_status	init_pipes(t_pipe_logic *pipes)
{
	if (NULL == pipes)
		return (FAILURE);
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
