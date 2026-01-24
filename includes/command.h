/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:13:55 by juperrin          #+#    #+#             */
/*   Updated: 2026/01/24 01:44:26 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "definitions.h"

typedef struct s_command
{
	char	*name;
	t_uint	max_arg;
	t_uint	min_arg;
	int		(*command)(void *);
}	t_command;

#endif