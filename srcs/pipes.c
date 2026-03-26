/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 14:13:45 by juperrin          #+#    #+#             */
/*   Updated: 2026/03/26 15:26:31 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_status	init_pipes(t_pipe_logic *pipes)
{
	if (NULL == pipes)
		return (FAILURE);
	pipes->redirect_output = false;
	pipes->redirect_input = false;
	pipes->input_pipe[0] = -1;
	pipes->input_pipe[1] = -1;
	pipes->output_pipe[0] = -1;
	pipes->output_pipe[1] = -1;
	pipes->pipe_index = 0;
	pipes->pipe_depth = 0;
	return (SUCCESS);
}
