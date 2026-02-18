/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 10:31:06 by juperrin          #+#    #+#             */
/*   Updated: 2026/02/18 11:22:58 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_dictionary	*init_env(char *envp[])
{
	t_dictionary	*dict;
	char			**tmp;

	dict = NULL;
	while (*envp)
	{
		tmp = split_at(*envp, '=');
		if (NULL == dict_add(&dict, tmp[0], tmp[1]))
		{
			free(tmp);
			dict_clear(&dict);
			return (NULL);
		}
		free(tmp);
		++envp;
	}
	return (dict);
}
