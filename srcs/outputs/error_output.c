/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 10:23:31 by juperrin          #+#    #+#             */
/*   Updated: 2026/02/09 13:03:09 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_status	error_output(const char *error)
{
	if (NULL == error)
		return (FAILURE);
	if (write(STDERR_FILENO, error, ft_strlen(error)) < 0)
	{
		error_output("Failed to write on stderr");
		return (FAILURE);
	}
	if (write(STDERR_FILENO, ".\n", 2) < 0)
	{
		error_output("Failed to write on stderr");
		return (FAILURE);
	}
	return (SUCCESS);
};
