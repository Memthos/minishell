/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 08:25:20 by juperrin          #+#    #+#             */
/*   Updated: 2026/02/18 11:31:18 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env(t_dictionary *env)
{
	if (NULL == env)
		return ;
	while (env)
	{
		printf("%s=%s\n", env->key, (char *)env->data);
		env = env->next;
	}
	return ;
}
