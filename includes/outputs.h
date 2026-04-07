/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outputs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 10:25:28 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/07 14:35:20 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OUTPUTS_H
# define OUTPUTS_H

# include "types.h"

/**
 * @brief Display an error on the stderr
 * @param error The error message to display
 * @return Returns 0 on success, 1 on failure
 */
t_status	error_output(const char *cmd, const char *arg, int error);

/// @brief Display an error from the parser on the stderr
/// @param arg The arg that failed.
/// @return Returns 0 on success, 1 on failure
t_status	parser_error_print(const char *arg);

/// @brief Print an error in case of ambiguous redirection.
/// @param arg THe node data.
/// @return Returns 0 on success, 1 on failure
t_status	amb_red_error_print(const char *arg);

/// @brief Display an error from the parser on the stderr
/// @param arg The arg that failed.
/// @return Returns 0 on success, 1 on failure
t_status	heredoc_error_print(const char *arg);

#endif
