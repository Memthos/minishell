/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 14:37:34 by juperrin          #+#    #+#             */
/*   Updated: 2026/03/31 10:23:06 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_command	get_built_in(t_uint idx)
{
	const t_command	built_ins[] = {
	{"echo", &cmd_echo},
	{"cd", &cmd_cd},
	{"pwd", &cmd_pwd},
	{"export", &cmd_export},
	{"unset", &cmd_unset},
	{"env", &cmd_env},
	{"exit", &cmd_exit}};

	return (built_ins[idx]);
}

t_built_in	get_command(char *name)
{
	t_uint		index;
	t_built_in	cmd;

	if (NULL == name)
		return (NULL);
	cmd = NULL;
	index = 0;
	while (index < CMD_COUNT)
	{
		if (!ft_strcmp(get_built_in(index).name, name))
		{
			cmd = get_built_in(index).cmd;
			break ;
		}
		++index;
	}
	if (NULL == cmd)
		cmd = &cmd_exec;
	return (cmd);
}

t_status	run_comand(t_shell *shell)
{
	t_status	code;
	pid_t		pid;
	t_built_in	cmd;

	if (NULL == shell || NULL == shell->cur_cmd || 0 == shell->cur_cmd_index)
		return (FAILURE);
	cmd = get_command(*shell->cur_cmd);
	if (0 == shell->pipes.pipe_depth && &cmd_exec != cmd)
	{
		if (-1 != shell->redirects.output_redirect_fd)
		{
			if (-1 == dup2(shell->redirects.output_redirect_fd, STDOUT_FILENO))
			{
				perror("dup2");
				ft_close(&shell->redirects.output_redirect_fd);
				shell->exitno = DUP_FAILURE;
				return (shell->exitno);
			}
			ft_close(&shell->redirects.output_redirect_fd);
		}
		else if (-1 != shell->redirects.output_cmp_redirect_fd)
		{
			if (-1 == dup2(shell->redirects.output_cmp_redirect_fd, STDOUT_FILENO))
			{
				perror("dup2");
				ft_close(&shell->redirects.output_cmp_redirect_fd);
				shell->exitno = DUP_FAILURE;
				return (shell->exitno);
			}
			ft_close(&shell->redirects.output_cmp_redirect_fd);
		}
		shell->exitno = cmd(shell->cur_cmd, shell);
		if (-1 == dup2(shell->redirects.stdout_dup, STDOUT_FILENO))
		{
			perror("dup2");
			shell->exitno = DUP_FAILURE;
		}
		return (shell->exitno);
	}
	pid = fork();
	if (-1 == pid)
	{
		shell->exitno = FORK_FAILURE;
		return (FORK_FAILURE);
	}
	if (0 == pid)
	{
		restore_signals();
		if (-1 != shell->redirects.input_redirect_fd)
		{
			if (-1 == dup2(shell->redirects.input_redirect_fd, STDIN_FILENO))
			{
				perror("dup2");
				destroy_shell(shell);
				exit(DUP_FAILURE);
			}
			ft_close(&shell->redirects.input_redirect_fd);
		}
		else if (-1 != shell->redirects.input_cmp_redirect_fd)
		{
			if (-1 == dup2(shell->redirects.input_cmp_redirect_fd, STDIN_FILENO))
			{
				perror("dup2");
				destroy_shell(shell);
				exit(DUP_FAILURE);
			}
			ft_close(&shell->redirects.input_cmp_redirect_fd);
		}
		if (-1 != shell->redirects.output_redirect_fd)
		{
			if (-1 == dup2(shell->redirects.output_redirect_fd, STDOUT_FILENO))
			{
				perror("dup2");
				destroy_shell(shell);
				exit(DUP_FAILURE);
			}
			ft_close(&shell->redirects.output_redirect_fd);
		}
		else if (-1 != shell->redirects.output_cmp_redirect_fd)
		{
			if (-1 == dup2(shell->redirects.output_cmp_redirect_fd, STDOUT_FILENO))
			{
				perror("dup2");
				destroy_shell(shell);
				exit(DUP_FAILURE);
			}
			ft_close(&shell->redirects.output_cmp_redirect_fd);
		}
		code = cmd(shell->cur_cmd, shell);
		destroy_shell(shell);
		exit(code);
	}
	ft_close(&shell->redirects.input_redirect_fd);
	ft_close(&shell->redirects.output_redirect_fd);
	shell->exitno = update_pids(shell, pid);
	return (shell->exitno);
}
