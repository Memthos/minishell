/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 14:37:34 by juperrin          #+#    #+#             */
/*   Updated: 2026/02/23 14:37:41 by juperrin         ###   ########.fr       */
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

void	init_commands(t_shell *shell)
{
	shell->commands = g_built_ins;
	return ;
}
