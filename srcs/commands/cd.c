/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 10:11:38 by juperrin          #+#    #+#             */
/*   Updated: 2026/02/19 15:25:06 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_status	cd(const char *path)
{
	if (NULL == path)
		return (FAILURE);
	if (count_words(path, "\t ") > 1)
	{
		error_output("cd : Too much arguments");
		return (FAILURE);
	}
	if (!ft_strcmp((char *)path, "-"))
	{
		path = getenv("OLDPWD");
		if (NULL == path)
		{
			error_output("cd: OLDPWD not set");
			return (FAILURE);
		}
		printf("%s\n", path);
	}
	if (SUCCESS != chdir(path))
	{
		perror("cd");
		return (FAILURE);
	}
	return (SUCCESS);
}
