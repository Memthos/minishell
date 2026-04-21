/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 13:20:07 by mperrine          #+#    #+#             */
/*   Updated: 2026/04/21 15:52:47 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_parent(t_shell *shell, pid_t pid, int pipe_fds[2])
{
	ft_close(&pipe_fds[1]);
	if (shell->redirects.is_cmp_redir)
	{
		ft_close(&shell->redirects.input_cmp_fd);
		shell->redirects.input_cmp_fd = pipe_fds[0];
	}
	else
	{
		ft_close(&shell->redirects.input_fd);
		shell->redirects.input_fd = pipe_fds[0];
	}
	waitpid(pid, (int *)&shell->exitno, 0);
	if (WIFEXITED(shell->exitno))
		shell->exitno = WEXITSTATUS(shell->exitno);
	if (WIFSIGNALED(shell->exitno))
		shell->exitno = WTERMSIG(shell->exitno) + 128;
}

static int	write_heredoc(t_shell *sh, t_ast_lst *node, int fd, t_strings data)
{
	size_t	i;

	if (sh->redirects.is_cmp_redir
		&& node->right->expand_state == HEREDOC_DENY)
		return (0);
	else if (node->left->expand_state == HEREDOC_DENY)
		return (0);
	i = 0;
	while ((*data)[i])
	{
		if ((*data)[i] == '$' && (*data)[i + 1])
		{
			if (expand_node(data, &i, sh, 0))
				return (1);
		}
		else
			i++;
	}
	write(fd, *data, ft_strlen(*data));
	write(fd, "\n", 1);
	free(*data);
	*data = NULL;
	return (0);
}

static t_string	heredoc_limiter(t_shell *shell, t_ast_lst *node)
{
	if (shell->redirects.is_cmp_redir)
		return (node->right->data);
	else
		return (node->left->data);
}

static int	heredoc_child(t_shell *shell, t_ast_lst *node, int pipe_fds[2])
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
			heredoc_error_print(heredoc_limiter(shell, node));
			break ;
		}
		if (!ret && ft_strcmp(read, heredoc_limiter(shell, node)) == 0)
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
		ft_close(&pipe_fds[0]);
		ft_close(&pipe_fds[1]);
		shell->exitno = FORK_FAILURE;
		return (1);
	}
	if (pid == 0)
	{
		heredoc_signals();
		ft_close(&pipe_fds[0]);
		heredoc_child(shell, node, pipe_fds);
	}
	heredoc_parent(shell, pid, pipe_fds);
	dup2(shell->redirects.stdin_dup, STDIN_FILENO);
	return (0);
}
