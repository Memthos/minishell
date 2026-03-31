/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 13:20:07 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/31 13:16:35 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	heredoc_to_input(t_shell *shell, char *data)
{
	int	pipe_fds[2];

	if (pipe(pipe_fds) == -1)
	{
		free(data);
		shell->exitno = PIPE_FAILURE;
		return (1);
	}
	write(pipe_fds[1], data, ft_strlen(data));
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
	return (0);
}

static int	expand_heredoc(t_shell *shell, t_ast_lst *node, char **data)
{
	size_t	i;

	if (node->expand_state == HEREDOC_DENY)
		return (0);
	i = 0;
	while ((*data)[i])
	{
		if ((*data)[i] == '$' && (*data)[i + 1])
		{
			if (update_expand_data(data, &i, shell))
			{
				shell->exitno = ALLOCATION_FAILURE;
				free(*data);
				return (1);
			}
		}
		else
			i++;
	}
	return (0);
}

static int	input_read(t_shell *shell, char *lim, char **data)
{
	char	*read;
	char	*tmp;

	while (1)
	{
		write (1, "> ", 2);
		read = get_next_line(0);
		if (ft_strcmp(read, lim) == 0)
		{
			free(read);
			break ;
		}
		tmp = ft_strjoin(*data, read);
		free(read);
		if (!tmp)
		{
			shell->exitno = ALLOCATION_FAILURE;
			return (1);
		}
		free(*data);
		*data = tmp;
	}
	return (0);
}

static int	read_heredoc(t_shell *shell, t_ast_lst *node, char **data)
{
	char	*lim;

	lim = ft_strjoin(node->data, "\n");
	if (!lim)
	{
		free(*data);
		shell->exitno = ALLOCATION_FAILURE;
		return (1);
	}
	if (input_read(shell, lim, data))
	{
		free(lim);
		free(*data);
		return (1);
	}
	free(lim);
	return (0);
}

int	heredoc(t_shell *shell, t_ast_lst *node)
{
	char		*data;

	data = calloc(1, 1);
	if (!data)
		return (1);
	if (read_heredoc(shell, node, &data))
		return (1);
	if (expand_heredoc(shell, node, &data))
		return (1);
	if (heredoc_to_input(shell, data))
		return (1);
	free(data);
	return (0);
}
