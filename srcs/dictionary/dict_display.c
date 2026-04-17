/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 11:43:24 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/17 11:35:46 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dict_display(t_dictionary *dict, t_string prefix, t_string sep,
	t_string suffix)
{
	while (dict)
	{
		printf("%s%s", prefix, dict->key);
		if (NULL != dict->data)
			printf("%s%s%s", sep, (t_string)dict->data, suffix);
		printf("\n");
		dict = dict->next;
	}
	return ;
}
