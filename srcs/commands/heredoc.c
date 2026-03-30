/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 13:20:07 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/30 16:40:51 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	expand_heredoc(t_shell *shell, t_hd_lst *heredoc, char **data)
{
	size_t	i;

	if (heredoc->node->expand_state == HEREDOC_DENY)
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

static int	read_heredoc(t_shell *shell, t_hd_lst *heredoc, char **data)
{
	char	*tmp;
	char	*read;
	char	*lim;

	read = NULL;
	lim = ft_strjoin(heredoc->node->data, "\n");
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

static int	get_heredoc_data(t_shell *shell, t_hd_lst *heredoc)
{
	int		pipe_fds[2];
	char	*data;

	data = calloc(1, 1);
	if (!data || read_heredoc(shell, heredoc, &data))
		return (1);
	if (pipe(pipe_fds) == -1)
	{
		shell->exitno = PIPE_FAILURE;
		return (1);
	}
	if (expand_heredoc(shell, heredoc, &data))
	{
		ft_close(&pipe_fds[0]);
		ft_close(&pipe_fds[1]);
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

int	heredocs_loop(t_shell *shell)
{
	t_hd_lst	*cur;

	cur = shell->heredoc.heredocs;
	while (cur)
	{
		if (get_heredoc_data(shell, cur))
		{
			heredoc_lst_clear(&shell->heredoc.heredocs);
			return (1);
		}
		cur = cur->next;
	}
	heredoc_lst_clear(&shell->heredoc.heredocs);
	return (0);
}
