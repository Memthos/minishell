/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 09:48:05 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/23 01:45:53 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	cmd_pwd(t_strings args, t_shell *shell)
{
	t_string	cwd;

	(void)args;
	cwd = get_cwd(shell);
	if (NULL == cwd)
		return (FAILURE);
	printf("%s\n", cwd);
	free(cwd);
	return (SUCCESS);
}

t_string	get_cwd(t_shell *shell)
{
	t_string		cwd;
	t_dictionary	*cwd_dict;

	cwd = getcwd(NULL, 0);
	if (cwd)
		return (cwd);
	cwd_dict = dict_get(shell->env, "PWD");
	if (NULL == cwd_dict)
		return (NULL);
	cwd = ft_strdup(cwd_dict->data);
	if (NULL == cwd)
		perror("malloc");
	return (cwd);
}
