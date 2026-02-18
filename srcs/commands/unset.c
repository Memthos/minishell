/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 09:10:34 by juperrin          #+#    #+#             */
/*   Updated: 2026/02/18 11:38:26 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_status	unset(t_dictionary **env, char *name)
{
	if (NULL == env || NULL == *env || NULL == name)
		return (FAILURE);
	if (NULL == dict_remove(env, name))
		return (FAILURE);
	return (SUCCESS);
}
