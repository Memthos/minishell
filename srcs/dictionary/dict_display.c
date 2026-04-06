/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 11:43:24 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/06 17:05:04 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	dict_display(t_dictionary *dict, char *prefix, char *sep, char *suffix)
{
	while (dict)
	{
		printf("%s%s", prefix, dict->key);
		if (NULL != dict->data)
			printf("%s%s%s", sep, (char *)dict->data, suffix);
		printf("\n");
		dict = dict->next;
	}
	return ;
}
