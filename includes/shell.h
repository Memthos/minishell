/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 10:48:47 by juperrin          #+#    #+#             */
/*   Updated: 2026/03/05 10:26:12 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "dictionary.h"
# include "lists.h"
# include "commands.h"
# include "lists.h"

typedef struct s_pipe_logic
{
	int	redirect;
	int	stdin_fd;
	int	stdout_fd;
	int	pipe_index;
}	t_pipe_logic;


typedef struct s_shell
{
	t_dictionary	*env;
	t_dictionary	*locals;
	t_ast_lst		*cmd_ast;
	char			**cur_cmd;
	t_uint			cur_cmd_index;
	t_status		exitno;
	t_pipe_logic	pipe_logic;
}	t_shell;

void	destroy(t_shell *shell);

t_status	update_locals(t_shell *shell, char *assign);

#endif
