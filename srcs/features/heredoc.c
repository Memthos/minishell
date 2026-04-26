/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 13:20:07 by mperrine          #+#    #+#             */
/*   Updated: 2026/04/26 18:41:59 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_parent(t_shell *shell, pid_t pid, int pipe_fds[2],
	t_status *status)
{
	ft_close(&pipe_fds[1]);
	ft_close(&shell->redirects.heredoc_fd);
	shell->redirects.heredoc_fd = pipe_fds[0];
	*status = wait_process(pid);
}

static int	write_heredoc(t_shell *sh, t_ast_lst *node, int fd, t_strings data)
{
	if (sh->redirects.is_cmp_redir
		&& node->right->expand_state == HEREDOC_ALLOW)
	{
		if (expand_heredoc(data, sh))
			return (1);
	}
	else if (!sh->redirects.is_cmp_redir
		&& node->left->expand_state == HEREDOC_ALLOW)
	{
		if (expand_heredoc(data, sh))
			return (1);
	}
	write(fd, *data, ft_strlen(*data));
	write(fd, "\n", 1);
	free(*data);
	*data = NULL;
	return (0);
}

static t_string	heredoc_limiter(t_ast_lst *node, bool is_cmp)
{
	if (is_cmp)
		return (node->right->data);
	else
		return (node->left->data);
}

static int	heredoc_child(t_shell *shell, t_ast_lst *node, int pipe_fds[2],
	bool is_cmp)
{
	t_string	read;
	int			ret;

	ret = 0;
	read = NULL;
	while (!ret)
	{
		read = readline("> ");
		if (g_signal == SIGINT)
			ret = 2;
		if (!ret && !read)
		{
			heredoc_error_print(heredoc_limiter(node, is_cmp));
			break ;
		}
		if (!ret && ft_strcmp(read, heredoc_limiter(node, is_cmp)) == 0)
			break ;
		if (!ret)
			ret = write_heredoc(shell, node, pipe_fds[1], &read);
	}
	if (read)
		free(read);
	ft_close(&pipe_fds[1]);
	destroy_shell(shell);
	exit (ret);
}

int	heredoc(t_shell *shell, t_ast_lst *node, bool is_cmp, t_status *status)
{
	int		pipe_fds[2];
	pid_t	pid;

	if (pipe(pipe_fds) == -1)
	{
		*status = PIPE_FAILURE;
		return (1);
	}
	pid = fork();
	if (pid == -1)
	{
		ft_close(&pipe_fds[0]);
		ft_close(&pipe_fds[1]);
		*status = FORK_FAILURE;
		return (1);
	}
	if (pid == 0)
	{
		heredoc_signals();
		ft_close(&pipe_fds[0]);
		heredoc_child(shell, node, pipe_fds, is_cmp);
	}
	heredoc_parent(shell, pid, pipe_fds, status);
	dup2(shell->redirects.stdin_dup, STDIN_FILENO);
	return (0);
}
