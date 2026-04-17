/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandle.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 00:37:53 by juperrin          #+#    #+#             */
/*   Updated: 2026/03/31 17:26:48 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGHANDLE_H
# define SIGHANDLE_H

# include "types.h"

extern int	g_signal;

/**
 * @brief Initialises the needed signals
 * @return SUCCESS on success, FAILURE otherwise
 */
t_status	init_normal_signals(void);

/**
 * @brief Initialises the 'execution signals',
 * that overrides 'normal signals' during execution.
 * @return 0 on success, 1 on failure.
 */
t_status	init_execution_signals(void);

/**
 * @brief Restores signal action to defaults.
 * Used to restore child signals actions.
 * @return 0 on success, 1 on failure.
 */
t_status	restore_signals(void);

/// @brief Initialises the 'heredoc signals',
///  * that overrides 'normal signals' during execution.
/// @return 0 on success, 1 on failure.
t_status	heredoc_signals(void);

#endif
