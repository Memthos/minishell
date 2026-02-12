/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 10:11:38 by juperrin          #+#    #+#             */
/*   Updated: 2026/02/12 08:07:24 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_status	cd(const char *path)
{
	if (NULL == path)
	{
		error_output("Empty path");
		return (FAILURE);
	}
	if (SUCCESS != chdir(path))
	{
		error_output("Failed to change current directory");
		return (FAILURE);
	}
	return (SUCCESS);
}
