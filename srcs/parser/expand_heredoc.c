/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 23:23:10 by mperrine          #+#    #+#             */
/*   Updated: 2026/04/25 23:39:16 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int	can_expand_heredoc(char *str, size_t i)
{
	if (str[i] == '$' && str[i + 1])
	{
		if (ft_isalnum(str[i + 1]) || str[i + 1] == '_')
			return (1);
		else if (str[i + 1] == '?' || str[i + 1] == '@' || str[i + 1] == '*'
			|| str[i + 1] == '#' || str[i + 1] == '$'
			|| str[i + 1] == '!' || str[i + 1] == '-')
			return (1);
	}
	return (0);
}

t_status	expand_heredoc(t_strings str, t_shell *shell)
{
	size_t		i;
	t_status	status;

	i = 0;
	status = SUCCESS;
	while (!status && *str && (*str)[i])
	{
		if (can_expand_heredoc(*str, i))
			status = expand_node(str, &i, shell, 0);
		else
			i++;
	}
	return (status);
}
