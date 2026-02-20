/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 09:48:05 by juperrin          #+#    #+#             */
/*   Updated: 2026/02/20 08:35:59 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_status	pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (NULL == path)
	{
		path = getenv("PWD");
		if (NULL == path)
		{
			error_output("cd : Failed to get current directory");
			return (FAILURE);
		}
		printf("%s\n", path);
		return (SUCCESS);
	}
	printf("%s\n", path);
	free(path);
	return (SUCCESS);
}
