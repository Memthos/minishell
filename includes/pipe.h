/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:15:39 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/23 12:50:11 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

typedef struct s_pipe
{
	t_side	side;
	int		pipe[2];	
}	t_pipe;

/**
 * @brief Creates an allocated t_pipe struct.
 */
t_pipe	*pipe_new(void);

/**
 * @brief Closes open fds in pipe and free it.
 */
void	pipe_close(t_pipe *pipe);

/**
 * @brief Returns the last pipe of the shell's pipe stack
 * with the corresponding side.
 */
t_pipe	*pipe_get(t_shell *shell, t_side side);
