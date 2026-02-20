/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 09:48:05 by juperrin          #+#    #+#             */
/*   Updated: 2026/02/20 10:48:39 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_status	cmd_pwd(char **args, t_dictionary **env_dict)
{
	t_dictionary	*PWD;
	char			*path;

	(void)args;
	path = getcwd(NULL, 0);
	if (NULL == path)
	{
		PWD = NULL;
		if (NULL != env_dict)
			PWD = dict_get(*env_dict, "PWD");
		if (NULL == PWD)
		{
			error_output("cd : failed to retrieve current working directory");
			return (FAILURE);
		}
		printf("%s\n", (char *)PWD->data);
		return (SUCCESS);
	}
	printf("%s\n", path);
	free(path);
	return (SUCCESS);
}
