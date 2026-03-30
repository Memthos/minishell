/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 13:20:07 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/30 15:31:27 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	expand_heredoc(t_shell *shell, char **data)
{
	size_t	i;

	if (shell->heredoc.lim->expand_state == HEREDOC_DENY)
		return (0);
	i = 0;
	while ((*data)[i])
	{
		if ((*data)[i] == '$' && (*data)[i + 1])
		{
			shell->exitno = update_expand_data(data, &i, shell);
			if (shell->exitno)
				return (1);
		}
		else
			i++;
	}
	return (0);
}

static int	here_doc_data(t_shell *shell, char **data)
{
	char	*tmp;
	char	*read;
	char	*lim;

	read = NULL;
	lim = ft_strjoin(shell->heredoc.lim->data, "\n");
	if (!lim)
	{
		shell->exitno = ALLOCATION_FAILURE;
		return (1);
	}
	while (1)
	{
		write (1, "> ", 2);
		read = get_next_line(0);
		if (!read)
			continue ;
		if (ft_strcmp(read, lim) == 0)
		{
			free(read);
			break ;
		}
		tmp = ft_strjoin(*data, read);
		free(*data);
		free(read);
		if (!tmp)
		{
			shell->exitno = ALLOCATION_FAILURE;
			free(lim);
			return (1);
		}
		*data = tmp;
	}
	free(lim);
	return (0);
}

int	get_heredoc_data(t_shell *shell)
{
	int		pipe_fds[2];
	char	*data;

	data = calloc(1, 1);
	if (!data || here_doc_data(shell, &data))
		return (1);
	if (pipe(pipe_fds) == -1)
	{
		shell->exitno = PIPE_FAILURE;
		return (1);
	}
	if (expand_heredoc(shell, &data))
	{
		ft_close(&pipe_fds[0]);
		ft_close(&pipe_fds[1]);
		return (1);
	}
	write(pipe_fds[1], data, ft_strlen(data));
	ft_close(&pipe_fds[1]);
	if (shell->redirects.is_cmp_redir)
		shell->redirects.input_cmp_redirect_fd = pipe_fds[0];
	else
		shell->redirects.input_redirect_fd = pipe_fds[0];
	return (0);
}
