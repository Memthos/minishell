/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 10:11:38 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/07 14:22:44 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_status	cmd_cd(char **args, t_shell *shell)
{
	t_dictionary	*dir;
	char			*path;

	if (NULL != args[1] && NULL != args[2])
	{
		error_output("cd", TOO_MUCH_ARG);
		return (FAILURE);
	}
	if (NULL == args[1])
	{
		dir = dict_get(shell->env, "HOME");
		if (NULL == dir)
		{
			error_output("cd : HOME not set", NO_ERR_MSG);
			return (FAILURE);
		}
		path = dir->data;
	}
	else if (!ft_strcmp(args[1], "-"))
	{
		dir = dict_get(shell->env, "OLDPWD");
		if (NULL == dir)
		{
			error_output("cd : OLDPWD not set", NO_ERR_MSG);
			return (FAILURE);
		}
		path = dir->data;
	}
	else
		path = args[1];
	if (SUCCESS != access(path, F_OK))
	{
		error_output(path, FILE_NOT_FOUND);
		return (1);
	}
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
