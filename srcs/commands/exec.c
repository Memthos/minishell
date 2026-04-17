/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 08:48:38 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/17 11:29:51 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_status	cmd_exec(t_strings args, t_shell *shell)
{
	t_dictionary	*path;
	t_uint			index;
	char			**paths;
	char			**envp;
	char			*tmp;

	paths = NULL;
	if (NULL == args || NULL == *args)
		return (FAILURE);
	if (SUCCESS != access(*args, F_OK))
	{
		if (str_is_empty(*args))
		{
			if (!check_path(shell))
				error_output(*args, NULL, FILE_NOT_FOUND);
			else
				error_output(*args, NULL, COMMAND_NOT_FOUND);
			return (127);
		}
		if (ft_strchr(*args, '/') || !check_path(shell))
		{
			error_output(*args, NULL, FILE_NOT_FOUND);
			return (127);
		}
		path = dict_get(shell->env, "PATH");
		paths = ft_split(path->data, ':');
		if (NULL == paths)
		{
			perror("malloc");
			return (FAILURE);
		}
		index = 0;
		while (*(paths + index))
		{
			tmp = ft_strjoin_sep(*(paths + index), *args, '/');
			if (NULL == tmp)
			{
				perror("malloc");
				++index;
				continue ;
			}
			if (SUCCESS == access(tmp, F_OK))
			{
				free(*args);
				*args = tmp;
				break ;
			}
			free(tmp);
			++index;
		}
		if (NULL == *(paths + index))
		{
			if (ft_strchr(*args, '/') || !check_path(shell))
				error_output(*args, NULL, FILE_NOT_FOUND);
			else
				error_output(*args, NULL, COMMAND_NOT_FOUND);
			strings_free(paths);
			return (127);
		}
	}
	if (ft_strchr(*args, '/') && is_dir(*args))
	{
		error_output(*args, NULL, IS_DIRECTORY);
		strings_free(paths);
		return (126);
	}
	envp = dict_to_array(shell->env, '=');
	execve(*args, args, envp);
	if (errno == ENOEXEC)
    {
        t_strings new_args = malloc(sizeof(t_string ) * (strings_len((const t_strings )args) + 2));
		*new_args = ft_strdup("/bin/sh");
		int index = 0;
		while (*(args + index))
		{
			*(new_args + index + 1) = ft_strdup(*(args + index));
			++index;
		}
		*(new_args + index + 1) = NULL;
        execve(*new_args, new_args, envp);
		strings_free(new_args);
	}
	strings_free(envp);
	strings_free(paths);
	if (SUCCESS == access(*args, X_OK) && !is_dir(*args))
		return (SUCCESS);
	if (SUCCESS != access(*args, X_OK) && SUCCESS == access(*args, R_OK | W_OK))
	{
		error_output(*args, NULL, COMMAND_NOT_FOUND);
		return (127);
	}
	if (SUCCESS != access(*args, R_OK | W_OK | X_OK))
	{
		error_output(*args, NULL, PERMISSION_ERROR);
		return (126);
	}
	error_output(*args, NULL, COMMAND_NOT_FOUND);
	return (127);
}
