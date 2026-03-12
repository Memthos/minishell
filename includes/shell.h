/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 10:48:47 by juperrin          #+#    #+#             */
/*   Updated: 2026/03/12 15:19:56 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "dictionary.h"
# include "lists.h"
# include "commands.h"
# include "lists.h"

typedef struct s_shell
{
	t_dictionary	*env;
	t_dictionary	*locals;
	t_ast_lst		*cmd_ast;
	char			**cur_cmd;
	t_uint			cur_cmd_index;
	t_status		exitno;
	bool			redirect_output;
	bool			redirect_input;
	int				pipe1[2];
	int				pipe2[2];
	t_uint			pipe_index;
	int				pipe_depth;
	pid_t			*pids;
	t_uint			pid_count;
	t_uint			pid_index;
}	t_shell;

void		destroy(t_shell *shell);

t_status	update_locals(t_shell *shell, char *assign);

#endif
