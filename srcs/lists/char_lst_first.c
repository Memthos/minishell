/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_lst_first.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 23:58:02 by mperrine          #+#    #+#             */
/*   Updated: 2026/04/26 00:27:01 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strcmp_lower(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && ft_tolower(s1[i]) == ft_tolower(s2[i]))
		i++;
	return (ft_tolower(s1[i]) - ft_tolower(s2[i]));
}

static int	is_before(t_string s1, t_string s2)
{
	if (!s1 || !*s1)
		return (1);
	if (!s2 || !*s2)
		return (0);
	if (ft_strcmp_lower(s1, s2) >= 0)
		return (1);
	return (0);
}

t_char_lst	**char_lst_first(t_char_lst **node)
{
	t_char_lst	**first;
	t_char_lst	**cur;

	if (!node || !*node)
		return (NULL);
	cur = node;
	first = node;
	while (*cur)
	{
		if (is_before((*first)->data, (*cur)->data))
			first = cur;
		cur = &(*cur)->next;
	}
	return (first);
}
