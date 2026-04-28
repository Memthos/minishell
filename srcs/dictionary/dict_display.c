/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 11:43:24 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/28 13:16:32 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dict_display(t_dictionary *dict, t_string prefix, t_string sep,
	t_string suffix)
{
	while (dict)
	{
		write(1, prefix, ft_strlen(prefix));
		write(1, dict->key, ft_strlen(dict->key));
		if (NULL != dict->data)
		{
			write(1, sep, ft_strlen(sep));
			write(1, (t_string)dict->data, ft_strlen((t_string)dict->data));
			write(1, suffix, ft_strlen(suffix));
		}
		write(1, "\n", 1);
		dict = dict->next;
	}
	return ;
}
