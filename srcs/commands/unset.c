/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 09:10:34 by juperrin          #+#    #+#             */
/*   Updated: 2026/02/18 09:55:30 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_status	unset(char *envp[], char *name)
{
	t_status	code;

	if (NULL == envp || NULL == name)
		return (FAILURE);
	code = SUCCESS;
	while (*envp)
	{
		if (!strncmp(*envp, name, ft_strlen(name)))
			break ;
		++envp;
	}
	if (NULL == *envp)
		code = FAILURE;
	while (*envp)
	{
		*envp = *(envp + 1);
		++envp;
	}
	return (code);
}
