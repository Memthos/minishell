/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 18:09:50 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/26 16:17:36 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_status	cmd_access(t_string *cmd, t_string path)
{
	t_string	tmp;

	if (NULL == path)
		return (FAILURE);
	tmp = ft_strjoin_sep(path, *cmd, '/');
	if (NULL == tmp)
	{
		perror("malloc");
		return (FAILURE);
	}
	if (SUCCESS == access(tmp, F_OK))
	{
		free(*cmd);
		*cmd = tmp;
		return (SUCCESS);
	}
	free(tmp);
	return (FAILURE);
}

static t_status	get_abs_path(t_string *cmd, t_dictionary *env)
{
	const t_dictionary	*path = dict_get(env, "PATH");
	t_uint				index;
	t_strings			path_arr;

	if (!cmd || cmd[0][0] == '\0'
		|| ft_strcmp(cmd[0], ".") == 0 || ft_strcmp(cmd[0], "..") == 0
		|| !path || ((t_string)path->data)[0] == '\0')
		return (SUCCESS);
	path_arr = ft_split(path->data, ':');
	if (NULL == path_arr)
	{
		perror("malloc");
		return (FAILURE);
	}
	index = 0;
	while (path_arr[index])
	{
		if (SUCCESS == cmd_access(cmd, path_arr[index++]))
			break ;
	}
	strings_free(path_arr);
	return (SUCCESS);
}

static t_status	check_is_dir(t_string cmd)
{
	if (is_dir(cmd))
	{
		error_output(cmd, NULL, IS_DIRECTORY);
		return (FAILURE);
	}
	return (SUCCESS);
}

t_status	check_access(t_string *cmd, t_dictionary *env)
{
	t_status	status;

	if (ft_strchr(cmd[0], '/'))
	{
		status = check_is_dir(*cmd);
		if (status)
			return (126);
		if (!status && access(cmd[0], F_OK) != 0 && !ft_strchr(cmd[0], '*'))
		{
			error_output(*cmd, NULL, FILE_NOT_FOUND);
			return (127);
		}
		else if (status == SUCCESS && access(cmd[0], X_OK) != 0)
		{
			error_output(*cmd, NULL, PERMISSION_ERROR);
			return (126);
		}
		if (status == SUCCESS && access(cmd[0], F_OK | X_OK) == 0)
			return (0);
	}
	status = get_abs_path(cmd, env);
	if (status == SUCCESS && access(cmd[0], F_OK) != 0)
	{
		if (!dict_get(env, "PATH"))
			error_output(*cmd, NULL, FILE_NOT_FOUND);
		else if (((t_string)dict_get(env, "PATH")->data)[0] == '\0')
			error_output(*cmd, NULL, COMMAND_NOT_FOUND);
		return (127);
	}
	return (status);
}
