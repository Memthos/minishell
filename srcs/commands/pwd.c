/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 09:48:05 by juperrin          #+#    #+#             */
/*   Updated: 2026/01/27 15:49:09 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_status	pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (NULL == path)
		return (PWD_ERROR);
	printf("%s\n", path);
	free(path);
	return (SUCCESS);
}
