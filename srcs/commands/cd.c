/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 10:11:38 by juperrin          #+#    #+#             */
/*   Updated: 2026/03/21 16:09:49 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_status	cmd_cd(char **args, t_shell *shell)
{
	t_dictionary	*dir;
	char			*path;

	if (NULL != args[1] && NULL != args[2])
	{
		error_output("cd : too many arguments", -1);
		return (FAILURE);
	}
	if (NULL == args[1])
	{
		dir = dict_get(shell->env, "HOME");
		if (NULL == dir)
		{
			error_output("cd : HOME not set", -1);
			return (FAILURE);
		}
		path = dir->data;
	}
	else if (!ft_strcmp(args[1], "-"))
	{
		dir = dict_get(shell->env, "OLDPWD");
		if (NULL == dir)
		{
			error_output("cd : OLDPWD not set", -1);
			return (FAILURE);
		}
		path = dir->data;
	}
	else
		path = args[1];
	if (NULL == dict_add(&shell->env, ft_strdup("OLDPWD"), get_cwd(shell)))
		perror("malloc");
	if (SUCCESS != chdir(path))
	{
		perror("cd");
		return (FAILURE);
	}
	if (NULL == dict_add(&shell->env, ft_strdup("PWD"), get_cwd(shell)))
		perror("malloc");
	return (SUCCESS);
}
