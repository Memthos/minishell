/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 14:37:34 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/17 11:06:18 by juperrin         ###   ########.fr       */
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

t_built_in	get_command(t_string name)
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
