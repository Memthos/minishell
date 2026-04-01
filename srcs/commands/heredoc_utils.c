/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 13:51:59 by mperrine          #+#    #+#             */
/*   Updated: 2026/04/01 13:53:33 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	input_read(t_shell *shell, char *lim, char **data)
{
	char	*read;
	char	*tmp;

	while (1)
	{
		write (1, "> ", 2);
		read = get_next_line(0);
		if (!read)
			break ;
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

int	read_heredoc(t_shell *shell, t_ast_lst *node, char **data)
{
	char	*lim;
	int		ret;

	ret = 0;
	if (shell->redirects.is_cmp_redir)
		lim = ft_strjoin(node->right->data, "\n");
	else
		lim = ft_strjoin(node->left->data, "\n");
	if (!lim)
	{
		shell->exitno = ALLOCATION_FAILURE;
		return (1);
	}
	if (input_read(shell, lim, data))
		ret = 1;
	free(lim);
	return (ret);
}
