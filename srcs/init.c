/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 02:21:00 by juperrin          #+#    #+#             */
/*   Updated: 2026/03/21 16:22:45 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_dictionary	*init_env(char *envp[])
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
	if (NULL == dict_add(&dict, ft_strdup("OLDPWD"), getcwd(NULL, 0)))
		perror("malloc");
	return (dict);
}

static void	set_shell(t_shell *shell)
{
	if (NULL == shell)
		return ;
	shell->cmd_ast = NULL;
	shell->cur_cmd = NULL;
	shell->exitno = SUCCESS;
	shell->cmp_depth = 0;
	init_pipes(&shell->pipes);
	shell->redirects.stdin_dup = dup(STDIN_FILENO);
	shell->redirects.stdout_dup = dup(STDOUT_FILENO);
	shell->redirects.is_cmp_redir = false;
	shell->redirects.output_redirect_fd = -1;
	shell->redirects.output_cmp_redirect_fd = -1;
	shell->redirects.input_redirect_fd = -1;
	shell->redirects.input_cmp_redirect_fd = -1;
	shell->heredoc.count = 0;
	shell->heredoc.max = 16;
	shell->heredoc.data = NULL;
	shell->pids.pids = NULL;
	shell->pids.pid_count = 0;
	shell->pids.pid_index = 0;
	return ;
}

t_shell	*init(char *envp[])
{
	t_shell	*shell;

	shell = (t_shell *)malloc(sizeof(t_shell));
	if (NULL == shell)
	{
		perror("malloc");
		return (NULL);
	}
	if (SUCCESS != init_signals())
	{
		free(shell);
		return (NULL);
	}
	shell->env = init_env(envp);
	if (NULL == shell->env)
	{
		free(shell);
		return (NULL);
	}
	set_shell(shell);
	return (shell);
}
