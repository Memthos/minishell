/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 12:51:11 by juperrin          #+#    #+#             */
/*   Updated: 2026/02/20 15:10:34 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_status	cmd_env(char **args, t_dictionary **env_dict)
{
	if (NULL == env_dict || NULL == *env_dict)
		return (FAILURE);
	if (NULL != args && NULL != *args)
		return (SUCCESS);
	dict_display(*env_dict, "=");
	return (SUCCESS);
}
