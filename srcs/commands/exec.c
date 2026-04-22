/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 08:48:38 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/22 15:02:26 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	check_access(t_string *cmd, t_dictionary *env);

static t_strings	sh_exec_init(const t_strings src)
{
	t_strings	args;

	args = malloc(sizeof(t_string) * (strings_len((const t_strings)src) + 2));
	if (NULL == args)
		return (NULL);
	*args = ft_strdup("/bin/sh");
	if (NULL == *args)
	{
		free(args);
		return (NULL);
	}
	return (args);
}

static t_status	sh_exec(t_strings args, t_strings envp)
{
	t_uint		index;
	t_strings	new_args;

	if (errno != ENOEXEC)
		return (SUCCESS);
	new_args = sh_exec_init((const t_strings)args);
	if (NULL == new_args)
		return (FAILURE);
	index = 0;
	while (*(args + index))
	{
		*(new_args + index + 1) = ft_strdup(*(args + index));
		if (NULL == *(new_args + index + 1))
		{
			strings_free(new_args);
			return (FAILURE);
		}
		++index;
	}
	*(new_args + index + 1) = NULL;
	execve(*new_args, new_args, envp);
	strings_free(new_args);
	return (SUCCESS);
}

static t_status	check_perms(t_strings args)
{
	if (SUCCESS == access(*args, X_OK) && !is_dir(*args))
		return (SUCCESS);
	if (SUCCESS != access(*args, X_OK))
	{
		if (!ft_strncmp(*args, "./", 2))
		{
			error_output(*args, NULL, PERMISSION_ERROR);
			return (126);
		}
		if (SUCCESS == access(*args, R_OK | W_OK))
		{
			error_output(*args, NULL, COMMAND_NOT_FOUND);
			return (127);
		}
	}
	if (SUCCESS != access(*args, R_OK | W_OK | X_OK))
	{
		error_output(*args, NULL, PERMISSION_ERROR);
		return (126);
	}
	error_output(*args, NULL, COMMAND_NOT_FOUND);
	return (127);
}

t_status	cmd_exec(t_strings args, t_shell *shell)
{
	t_status	status;
	char		**envp;

	if (NULL == args || NULL == *args)
		return (FAILURE);
	status = check_access(args, shell->env);
	if (SUCCESS != status)
		return (status);
	envp = dict_to_array(shell->env, '=');
	execve(*args, args, envp);
	status = sh_exec(args, envp);
	if (SUCCESS != status)
	{
		perror("malloc");
		strings_free(envp);
		return (status);
	}
	strings_free(envp);
	status = check_perms(args);
	return (status);
}
