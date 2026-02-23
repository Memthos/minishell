/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 09:48:05 by juperrin          #+#    #+#             */
/*   Updated: 2026/02/23 17:46:02 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_status	cmd_pwd(char **args, t_shell *shell)
{
	t_dictionary	*pwd_env;
	char			*path;

	(void)args;
	path = getcwd(NULL, 0);
	if (NULL == path)
	{
		pwd_env = NULL;
		if (NULL != shell->env)
			pwd_env = dict_get(shell->env, "PWD");
		if (NULL == pwd_env)
		{
			error_output("cd : failed to retrieve current working directory");
			return (FAILURE);
		}
		printf("%s\n", (char *)pwd_env->data);
		return (SUCCESS);
	}
	printf("%s\n", path);
	free(path);
	return (SUCCESS);
}
