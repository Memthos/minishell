/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 09:48:05 by juperrin          #+#    #+#             */
/*   Updated: 2026/03/21 15:49:32 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_status	cmd_pwd(char **args, t_shell *shell)
{
	t_dictionary	*pwd_env;
	char			*path;

	(void)args;
	pwd_env = dict_get(shell->env, "PWD");
	if (pwd_env)
	{
		printf("%s\n", (char *)pwd_env->data);
		return (SUCCESS);
	}
	path = getcwd(NULL, 0);
	if (NULL == path)
	{
		perror("pwd");
		return (FAILURE);
	}
	printf("%s\n", path);
	free(path);
	return (SUCCESS);
}
