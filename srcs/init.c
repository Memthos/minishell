/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 02:21:00 by juperrin          #+#    #+#             */
/*   Updated: 2026/02/19 09:16:43 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_status	init(char *envp[])
{
	t_dictionary	*env_dict;

	if (SUCCESS != init_signals())
		return (FAILURE);
	env_dict = init_env(envp);
	if (NULL == env_dict)
		return (FAILURE);
	return (SUCCESS);
}
