/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:47:29 by mperrine          #+#    #+#             */
/*   Updated: 2026/01/27 15:13:41 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_io_number_t(t_list *lst)
{
	size_t	i;

	if (!lst || !lst->data)
		return ;
	i = 0;
	while (lst->data[i] && lst->data[i] >= '0' && lst->data[i] <= '9')
		i++;
	if (i == ft_strlen(lst->data))
		lst->token = IO_NUMBER;
}

char	*make_str(char *input, size_t len)
{
	char	*s;
	size_t	i;

	s = malloc(sizeof(char) * (len + 1));
	if (!s)
		return (NULL);
	s[len] = '\0';
	i = 0;
	while (i++ < len)
		s[i - 1] = input[i - 1];
	return (s);
}

int	is_newline(char *s, size_t *index)
{
	if (s[0] == '\\' && (s[1] == 't' || s[1] == 'n'
			|| s[1] == 'v' || s[1] == 'f' || s[1] == 'r'))
	{
		(*index)++;
		return (1);
	}
	return (0);
}
