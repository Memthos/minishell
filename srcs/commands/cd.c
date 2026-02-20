/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 10:11:38 by juperrin          #+#    #+#             */
/*   Updated: 2026/02/20 10:48:27 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_status	cmd_cd(char **args, t_dictionary **env)
{
	t_dictionary	*dir;
	char			*path;

	if (NULL != args && NULL != *args && NULL != *(args + 1))
	{
		error_output("cd : too many arguments");
		return (FAILURE);
	}
	path = NULL;
	if (NULL == args || NULL == *args)
	{
		dir = dict_get(*env, "HOME");
		if (NULL == dir)
		{
			error_output("cd : HOME not set");
			return (FAILURE);
		}
		path = dir->data;
	}
	else if (!ft_strcmp(*args, "-"))
	{
		dir = dict_get(*env, "OLDPWD");
		if (NULL == dir)
		{
			error_output("cd : OLDPWD not set");
			return (FAILURE);
		}
		path = dir->data;
	}
	else
		path = *args;
	if (SUCCESS != chdir(path))
	{
		perror("cd");
		return (FAILURE);
	}
	return (SUCCESS);
}
