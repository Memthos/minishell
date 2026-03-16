/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 02:22:04 by juperrin          #+#    #+#             */
/*   Updated: 2026/03/16 14:20:26 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "definitions.h"

/**
 * @brief Initialises Minishell.
 */
t_shell			*init(char *envp[]);

#endif