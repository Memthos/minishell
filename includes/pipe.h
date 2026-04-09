/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:15:39 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/09 17:03:09 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

typedef struct s_pipe
{
	t_side	side;
	int		pipe[2];	
}	t_pipe;

t_pipe	*pipe_new(void);

void	pipe_close(t_pipe *pipe);

t_pipe	*pipe_get(t_shell *shell, t_side side);
