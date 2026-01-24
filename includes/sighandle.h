/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandle.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 00:37:53 by juperrin          #+#    #+#             */
/*   Updated: 2026/01/24 01:52:23 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGHANDLE_H
# define SIGHANDLE_H

# include "minishell.h"

extern int	g_signal;

/**
 * 
 */
t_status	init_signals(void);

/**
 * 
 */
void		sig_intercept(int signo, siginfo_t *info, void *other);

#endif