/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 14:04:51 by mperrine          #+#    #+#             */
/*   Updated: 2026/04/28 14:34:31 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_string	get_prompt_pwd(t_shell *shell)
{
	t_string		path;
	const t_string	pwd = get_cwd(shell);
	const t_string	home = dict_get_data(shell->env, "HOME");
	size_t			i;

	if (!pwd || !home)
	{
		if (pwd)
			free(pwd);
		return (NULL);
	}
	i = 0;
	while (pwd[i] && home[i] && pwd[i] == home[i])
		i++;
	path = ft_calloc(ft_strlen(&pwd[i]) + 2, 1);
	if (!path)
	{
		free(pwd);
		return (NULL);
	}
	path[0] = '~';
	ft_strlcat(path, &pwd[i], ft_strlen(&pwd[i]) + 2);
	free(pwd);
	return (path);
}

static void	set_prompt(t_string *prompt, t_string user, t_string hostname,
	t_string path)
{
	ft_strlcpy(*prompt, user, ft_strlen(user) + 1);
	ft_strlcat(*prompt, "@", ft_strlen(user) + 2);
	ft_strlcat(*prompt, hostname, ft_strlen(user) + 5);
	ft_strlcat(*prompt, ":", ft_strlen(user) + 6);
	ft_strlcat(*prompt, path, ft_strlen(user) + ft_strlen(path) + 6);
	ft_strlcat(*prompt, "$ ", ft_strlen(user) + ft_strlen(path) + 8);
}

t_status	get_prompt(t_shell *shell, t_string *prompt)
{
	t_status		status;
	const t_string	user = dict_get_data(shell->env, "USER");
	const t_string	path = get_prompt_pwd(shell);
	char			hostname[4];
	int				fd;

	if (!user || !path)
		return (FAILURE);
	status = SUCCESS;
	hostname[3] = '\0';
	fd = open("/etc/hostname", O_RDONLY);
	if (-1 == fd)
		status = FAILURE;
	if (!status && -1 == read(fd, hostname, 3))
		status = FAILURE;
	if (!status)
		*prompt = ft_calloc(ft_strlen(user) + ft_strlen(path) + 8, 1);
	if (!*prompt)
		status = FAILURE;
	if (!status)
		set_prompt(prompt, user, hostname, path);
	if (-1 != fd)
		close(fd);
	free(path);
	return (status);
}
