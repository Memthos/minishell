/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 14:37:34 by juperrin          #+#    #+#             */
/*   Updated: 2026/03/19 09:22:29 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static const t_command	g_built_in_echo = {"echo", &cmd_echo};
static const t_command	g_built_in_cd = {"cd", &cmd_cd};
static const t_command	g_built_in_pwd = {"pwd", &cmd_pwd};
static const t_command	g_built_in_export = {"export", &cmd_export};
static const t_command	g_built_in_unset = {"unset", &cmd_unset};
static const t_command	g_built_in_env = {"env", &cmd_env};
static const t_command	g_built_in_exit = {"exit", &cmd_exit};

static const t_command	*g_built_ins[] = {
	&g_built_in_echo,
	&g_built_in_cd,
	&g_built_in_pwd,
	&g_built_in_export,
	&g_built_in_unset,
	&g_built_in_env,
	&g_built_in_exit
};

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
		if (!ft_strcmp(g_built_ins[index]->name, name))
		{
			cmd = g_built_ins[index]->cmd;
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
		dprintf(2, "%s : %d\n", *shell->cur_cmd, shell->exitno);
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
		if (shell->pipes.redirect_input)
		{
			if (0 == (shell->pipes.pipe_index - 1) % 2)
			{
				if (-1 == dup2(shell->pipes.pipe1[0], STDIN_FILENO))
				{
					destroy_shell(shell);
					exit(DUP_FAILURE);
				}
				ft_close(&shell->pipes.pipe1[0]);
				ft_close(&shell->pipes.pipe1[1]);
			}
			else
			{
				if (-1 == dup2(shell->pipes.pipe2[0], STDIN_FILENO))
				{
					destroy_shell(shell);
					exit(DUP_FAILURE);
				}
				ft_close(&shell->pipes.pipe2[0]);
				ft_close(&shell->pipes.pipe2[1]);
			}
		}
		if (shell->pipes.redirect_output)
		{
			if (0 == shell->pipes.pipe_index % 2)
			{
				if (-1 == dup2(shell->pipes.pipe1[1], STDOUT_FILENO))
				{
					perror("dup2");
					destroy_shell(shell);
					exit(DUP_FAILURE);
				}
				ft_close(&shell->pipes.pipe1[0]);
				ft_close(&shell->pipes.pipe1[1]);
			}
			else
			{
				if (-1 == dup2(shell->pipes.pipe2[1], STDOUT_FILENO))
				{
					perror("dup2");
					destroy_shell(shell);
					exit(DUP_FAILURE);
				}
				ft_close(&shell->pipes.pipe2[0]);
				ft_close(&shell->pipes.pipe2[1]);
			}
		}
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
		dprintf(2, "%s : %d\n", *shell->cur_cmd, code);
		destroy_shell(shell);
		exit(code);
	}
	ft_close(&shell->redirects.input_redirect_fd);
	ft_close(&shell->redirects.output_redirect_fd);
	shell->exitno = update_pids(shell, pid);
	return (shell->exitno);
}
