/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 10:11:38 by juperrin          #+#    #+#             */
/*   Updated: 2026/02/12 08:16:28 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_status	cd(const char *path)
{
	if (NULL == path)
		return (FAILURE);
	if (SUCCESS != chdir(path))
	{
		perror("Failed to change current directory");
		return (FAILURE);
	}
	return (SUCCESS);
}
