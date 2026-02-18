/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 11:43:24 by juperrin          #+#    #+#             */
/*   Updated: 2026/02/18 11:46:47 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	dict_display(t_dictionary *dict)
{
	while (dict)
	{
		printf("%s : %s\n", dict->key, (char *)dict->data);
		dict = dict->next;
	}	
}
