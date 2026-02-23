/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 11:43:24 by juperrin          #+#    #+#             */
/*   Updated: 2026/02/23 09:38:27 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	dict_display(t_dictionary *dict, char *prefix, char *sep)
{
	while (dict)
	{
		printf("%s%s%s%s\n", prefix, dict->key, sep, (char *)dict->data);
		dict = dict->next;
	}
	return ;
}
