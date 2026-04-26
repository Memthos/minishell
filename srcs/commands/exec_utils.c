/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 18:09:50 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/25 23:12:49 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_status	check_special_cases(t_string cmd, t_dictionary *env)
{
	if (str_is_empty(cmd))
	{
		if (!check_env_path(env))
			error_output(cmd, NULL, FILE_NOT_FOUND);
		else
			error_output(cmd, NULL, COMMAND_NOT_FOUND);
		return (FAILURE);
	}
	if (ft_strchr(cmd, '/') || !check_env_path(env))
	{
		error_output(cmd, NULL, FILE_NOT_FOUND);
		return (FAILURE);
	}
	return (SUCCESS);
}

static t_status	cmd_access(t_string *cmd, t_string path)
{
	t_string	tmp;

	if (NULL == path)
	{
		perror("malloc");
		return (FAILURE);
	}
	tmp = ft_strjoin_sep(path, *cmd, '/');
	if (NULL == tmp)
	{
		free(path);
		perror("malloc");
		return (FAILURE);
	}
	free(path);
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

	path_arr = ft_split(path->data, ':');
	if (NULL == path_arr)
	{
		perror("malloc");
		return (FAILURE);
	}
	index = 0;
	while (*(path_arr + index))
	{
		if (SUCCESS == cmd_access(cmd, ft_strdup(*(path_arr + index))))
			break ;
		++index;
	}
	if (NULL == *(path_arr + index))
	{
		error_output(*cmd, NULL, COMMAND_NOT_FOUND);
		strings_free(path_arr);
		return (127);
	}
	strings_free(path_arr);
	return (SUCCESS);
}

static t_status	check_is_dir(t_string cmd)
{
	if (ft_strchr(cmd, '/') && is_dir(cmd))
	{
		error_output(cmd, NULL, IS_DIRECTORY);
		return (FAILURE);
	}
	return (SUCCESS);
}

t_status	check_access(t_string *cmd, t_dictionary *env)
{
	t_status	status;

	if (SUCCESS != access(*cmd, F_OK | X_OK))
	{
		if (SUCCESS != check_special_cases(*cmd, env))
			return (127);
		status = get_abs_path(cmd, env);
		if (SUCCESS != status)
			return (status);
	}
	if (SUCCESS != check_is_dir(*cmd))
		return (126);
	return (SUCCESS);
}
