/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 08:25:20 by juperrin          #+#    #+#             */
/*   Updated: 2026/02/18 09:02:57 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env(char *envp[])
{
	if (NULL == envp)
		return ;
	while (*envp)
	{
		printf("%s\n", *envp);
		++envp;
	}
	return ;
}
