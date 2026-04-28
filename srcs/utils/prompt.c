/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 14:04:51 by mperrine          #+#    #+#             */
/*   Updated: 2026/04/28 16:14:00 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_string	get_prompt_pwd(t_shell *shell)
{
	t_string		path;
	const t_string	pwd = get_cwd(shell);
	const t_string	home = dict_get_data(shell->env, "HOME");

	if (!pwd)
		return (NULL);
	if (ft_strncmp(pwd, home, ft_strlen(home)) != 0)
		path = ft_calloc(ft_strlen(pwd) + 1, 1);
	else
		path = ft_calloc(ft_strlen(pwd + ft_strlen(home)) + 2, 1);
	if (path && ft_strncmp(pwd, home, ft_strlen(home)) == 0)
	{
		if (home)
		{
			path[0] = '~';
			ft_strlcat(path, pwd + ft_strlen(home),
				ft_strlen(pwd + ft_strlen(home)) + 2);
		}
		else
			ft_strlcpy(path, pwd, ft_strlen(pwd) + 1);
	}
	else if (path)
		ft_strlcpy(path, pwd, ft_strlen(pwd) + 1);
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

static void	get_hostname(char (*hostname)[4])
{
	int		fd;

	fd = open("/etc/hostname", O_RDONLY);
	if (-1 == fd)
		return ;
	if (-1 == read(fd, *hostname, 3))
	{
		close(fd);
		return ;
	}
	(*hostname)[3] = '\0';
	close(fd);
}

t_status	get_prompt(t_shell *shell, t_string *prompt)
{
	const t_string	user = dict_get_data(shell->env, "USER");
	const t_string	path = get_prompt_pwd(shell);
	char			hostname[4];

	if (!user || !path)
	{
		if (path)
			free(path);
		return (FAILURE);
	}
	hostname[0] = '\0';
	get_hostname(&hostname);
	if (hostname[0] == '\0')
	{
		free(path);
		return (FAILURE);
	}
	*prompt = ft_calloc(ft_strlen(user) + ft_strlen(path) + 8, 1);
	if (*prompt)
		set_prompt(prompt, user, hostname, path);
	free(path);
	if (!*prompt)
		return (FAILURE);
	return (SUCCESS);
}
