/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 08:25:20 by juperrin          #+#    #+#             */
/*   Updated: 2026/02/18 08:26:48 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_status	penv(void)
{
	char	*env;

	env = getenv(NULL);
	if (NULL == env)
		return (FAILURE);
	printf("%s\n", env);
	return (SUCCESS);	
}
