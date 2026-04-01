/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 13:20:07 by mperrine          #+#    #+#             */
/*   Updated: 2026/04/01 13:52:38 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	expand_heredoc(t_shell *shell, t_ast_lst *node, char **data)
{
	size_t	i;

	if (shell->redirects.is_cmp_redir
		&& node->right->expand_state == HEREDOC_DENY)
		return (0);
	else if (node->left->expand_state == HEREDOC_DENY)
		return (0);
	i = 0;
	while ((*data)[i])
	{
		if ((*data)[i] == '$' && (*data)[i + 1])
		{
			if (update_expand_data(data, &i, shell))
			{
				shell->exitno = ALLOCATION_FAILURE;
				return (1);
			}
		}
		else
			i++;
	}
	return (0);
}

static int	heredoc_child(t_shell *shell, t_ast_lst *node, int pipe_fds[2])
{
	char	*data;
	int		ret;

	ret = 0;
	ft_close(&pipe_fds[0]);
	heredoc_signals();
	data = calloc(1, 1);
	if (!data)
		return (1);
	if (!ret && read_heredoc(shell, node, &data))
		ret = 1;
	if (!ret && expand_heredoc(shell, node, &data))
		ret = 1;
	if (!ret)
		write(pipe_fds[1], data, ft_strlen(data));
	ft_close(&pipe_fds[1]);
	free(data);
	destroy_shell(shell);
	exit(ret);
}

void	wait_child(t_shell *shell, pid_t pid, int pipe_fds[2])
{
	ft_close(&pipe_fds[1]);
	if (shell->redirects.is_cmp_redir)
	{
		ft_close(&shell->redirects.input_cmp_redirect_fd);
		shell->redirects.input_cmp_redirect_fd = pipe_fds[0];
	}
	else
	{
		ft_close(&shell->redirects.input_redirect_fd);
		shell->redirects.input_redirect_fd = pipe_fds[0];
	}
	waitpid(pid, (int *)&shell->exitno, 0);
	if (WIFEXITED(shell->exitno))
		shell->exitno = WEXITSTATUS(shell->exitno);
	if (WIFSIGNALED(shell->exitno))
		shell->exitno = WTERMSIG(shell->exitno) + 128;
}

int	heredoc(t_shell *shell, t_ast_lst *node)
{
	int		pipe_fds[2];
	pid_t	pid;

	if (pipe(pipe_fds) == -1)
	{
		shell->exitno = PIPE_FAILURE;
		return (1);
	}
	pid = fork();
	if (pid == -1)
	{
		shell->exitno = FORK_FAILURE;
		return (1);
	}
	if (pid == 0)
		heredoc_child(shell, node, pipe_fds);
	wait_child(shell, pid, pipe_fds);
	return (0);
}
