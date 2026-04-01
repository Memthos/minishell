/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 13:20:07 by mperrine          #+#    #+#             */
/*   Updated: 2026/04/01 19:07:32 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	write_heredoc(t_shell *shell, t_ast_lst *node, int fd, char **data)
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
	write(fd, *data, ft_strlen(*data));
	write(fd, "\n", 1);
	return (0);
}

static int	input_read(t_shell *shell, char *lim, t_ast_lst *node, int *fd)
{
	char	*read;
	int		ret;

	ret = 0;
	while (!ret)
	{
		read = readline("> ");
		if (g_signal == SIGINT)
			break ;
		if (!read)
		{
			heredoc_error_print(lim);
			break ;
		}
		if (ft_strcmp(read, lim) == 0)
			break ;
		if (write_heredoc(shell, node, *fd, &read))
			ret = 1;
		free(read);
	}
	if (read)
		free(read);
	ft_close(fd);
	return (ret);
}

static int	read_heredoc(t_shell *shell, t_ast_lst *node, int *fd)
{
	char	*lim;

	if (shell->redirects.is_cmp_redir)
		lim = node->right->data;
	else
		lim = node->left->data;
	if (input_read(shell, lim, node, fd))
	{
		shell->exitno = ALLOCATION_FAILURE;
		return (1);
	}
	return (0);
}

int	heredoc(t_shell *shell, t_ast_lst *node)
{
	int	pipe_fds[2];

	heredoc_signals();
	if (pipe(pipe_fds) == -1)
	{
		shell->exitno = PIPE_FAILURE;
		return (1);
	}
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
	if (read_heredoc(shell, node, &pipe_fds[1]))
		return (1);
	return (0);
}
