/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 09:48:05 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/07 13:30:56 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_status	cmd_pwd(char **args, t_shell *shell)
{
	char	*cwd;

	(void)args;
	cwd = get_cwd(shell);
	if (NULL == cwd)
		return (FAILURE);
	printf("%s\n", cwd);
	free(cwd);
	return (SUCCESS);
}

char	*get_cwd(t_shell *shell)
{
	char			*cwd;
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
