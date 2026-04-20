/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 10:11:38 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/20 14:45:08 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_string	cd_home(t_dictionary *env)
{
	const t_dictionary	*dir = dict_get(env, "HOME");

	if (NULL == dir)
	{
		error_output("cd", "HOME not set", NO_ERR_MSG);
		return (NULL);
	}
	return (dir->data);
}

static t_string	cd_oldpwd(t_dictionary *env)
{
	const t_dictionary	*dir = dict_get(env, "OLDPWD");

	if (NULL == dir)
	{
		error_output("cd", "OLDPWD not set", NO_ERR_MSG);
		return (NULL);
	}
	return (dir->data);
}

static t_string	cd_get_path(t_strings args, t_dictionary *env)
{
	char			*path;

	if (NULL == args[1])
	{
		path = cd_home(env);
		if (NULL == path)
			return (NULL);
	}
	else if (!ft_strcmp(args[1], "-"))
	{
		path = cd_oldpwd(env);
		if (NULL == path)
			return (NULL);
	}
	else
		path = args[1];
	return (path);
}

static t_status	cd_exec(t_string path, t_shell *shell)
{
	char			*cur_dir;

	if (NULL == dict_add(&shell->env, ft_strdup("OLDPWD"), get_cwd(shell)))
		perror("malloc");
	if (SUCCESS != chdir(path))
	{
		perror("cd");
		return (FAILURE);
	}
	if (NULL == dict_add(&shell->env, ft_strdup("PWD"), get_cwd(shell)))
		perror("malloc");
	cur_dir = getcwd(NULL, 0);
	if (NULL == cur_dir)
		error_output("cd", path, FILE_NOT_FOUND);
	free(cur_dir);
	return (SUCCESS);
}

t_status	cmd_cd(t_strings args, t_shell *shell)
{
	t_status	status;
	t_string	path;

	if (NULL != args[1] && NULL != args[2])
	{
		error_output("cd", NULL, TOO_MUCH_ARG);
		return (FAILURE);
	}
	path = cd_get_path(args, shell->env);
	if (NULL == path)
		return (FAILURE);
	if (SUCCESS != access(path, F_OK))
	{
		error_output("cd", path, FILE_NOT_FOUND);
		return (FAILURE);
	}
	status = cd_exec(path, shell);
	return (status);
}
