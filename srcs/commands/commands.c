/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 14:37:34 by juperrin          #+#    #+#             */
/*   Updated: 2026/03/11 16:13:35 by juperrin         ###   ########.fr       */
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
	if (0 == shell->pipe_depth && &cmd_exec != cmd)
	{
		code = cmd(shell->cur_cmd, shell);
		printf("'%s' return %d\n", *shell->cur_cmd, code);
		return (code);
	}
	pid = fork();
	if (-1 == pid)
	{
		free(shell->cur_cmd);
		return (FORK_FAILURE);
	}
	if (0 == pid)
	{
		printf("Entering sub-process\n");
		printf("Needed redirection will be applied here\n");
		code = cmd(shell->cur_cmd, shell);
		printf("'%s' return %d\n", *shell->cur_cmd, code);
		destroy(shell);
		printf("Exiting sub-process\n");
		exit(code);
	}
	shell->pids = increment_array(shell->pids, shell->pid_count, sizeof(pid_t));
	if (NULL == shell->pids)
		return (ALLOCATION_FAILURE);
	shell->pids[shell->pid_count] = pid;
	++shell->pid_count;
	printf("Added %d in pids list\n", pid);
	return (SUCCESS);
}
