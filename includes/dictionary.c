/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 11:10:37 by juperrin          #+#    #+#             */
/*   Updated: 2026/02/17 11:22:12 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DICTIONARY_H
# define DICTIONARY_H

# include "definitions.h"

typedef struct s_dictionary
{
	char				*key;
	void				*data;
	struct s_dictionary	*next;
}						t_dictionary;

#endif