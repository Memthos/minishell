/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 08:48:38 by juperrin          #+#    #+#             */
/*   Updated: 2026/03/30 16:42:00 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_status	cmd_exec(char **args, t_shell *shell)
{
	t_dictionary	*path;
	t_uint			index;
	char			**paths;
	char			**envp;
	char			*tmp;

	paths = NULL;
	if (NULL == args || NULL == *args)
		return (FAILURE);
	if (access(*args, F_OK | X_OK) < 0)
	{
		if (ft_strchr(*args, '/') || !check_path(shell))
		{
			perror(*args);
			return (127);
		}
		if (!check_path(shell))
		{
			error_output(*args, COMMAND_NOT_FOUND);
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
			if (!access(tmp, F_OK | X_OK))
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
				perror(*args);
			else
				error_output(*args, COMMAND_NOT_FOUND);
			free_strings(paths);
			return (127);
		}
	}
	envp = dict_to_array(shell->env, '=');
	execve(*args, args, envp);
	perror(*args);
	free_strings(envp);
	free_strings(paths);
	return (SUCCESS);
}
