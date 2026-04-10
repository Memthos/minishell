/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 10:48:47 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/09 17:45:35 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "dictionary.h"
# include "lists.h"
# include "stack_lst.h"
# include "commands.h"

typedef struct s_redir_logic
{
	int		stdout_dup;
	int		stdin_dup;
	bool	is_cmp_redir;
	int		output_redirect_fd;
	int		output_cmp_redirect_fd;
	int		input_redirect_fd;
	int		input_cmp_redirect_fd;
	t_uint	out_flags;
	t_uint	in_flags;
}	t_redir_logic;

typedef struct s_pids_logic
{
	pid_t	*pids;
	t_uint	pid_count;
	t_uint	pid_index;
}	t_pids_logic;

typedef struct s_shell
{
	t_dictionary	*env;
	t_cmd_lst		*cmd_ast;
	char			**cur_cmd;
	t_uint			cur_cmd_index;
	t_status		exitno;
	t_status		oldexitno;
	t_stack			*pipe_stack;
	int				redirect_output;
	int				redirect_input;
	t_redir_logic	redirects;
	t_pids_logic	pids;
	t_uint8			heredoc_max;
	t_uint			cmp_depth;
}	t_shell;

/**
 * @brief Adds pid to the list of pids in shell.
 */
t_status	update_pids(t_shell *shell, pid_t pid);

/**
 * @brief If pids list is not null, wait for all pid in pids
 * to finish their execution.
 */
t_status	wait_for_processes(t_shell *shell);

/**
 * @brief Destroys all allocated ressources that have bee not
 * freed, and closes all fd that are opened.
 */
void		destroy_shell(t_shell *shell);

#endif
