/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandle.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 00:37:53 by juperrin          #+#    #+#             */
/*   Updated: 2026/03/23 13:24:58 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGHANDLE_H
# define SIGHANDLE_H

# include "minishell.h"

extern int	g_signal;

/**
 * @brief Initialises the needed signals
 * @return SUCCESS on success, FAILURE otherwise
 */
t_status	init_normal_signals(void);

#endif