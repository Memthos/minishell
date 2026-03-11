/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 10:48:47 by juperrin          #+#    #+#             */
/*   Updated: 2026/03/11 09:18:46 by juperrin         ###   ########.fr       */
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
	int				pipe1[2];
	int				pipe2[2];
	t_uint			pipe_index;
	pid_t			*pids;
	t_uint			pids_count;
	t_uint			pids_index;
}	t_shell;

void		destroy(t_shell *shell);

t_status	update_locals(t_shell *shell, char *assign);

#endif
