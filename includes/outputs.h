/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outputs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 10:25:28 by juperrin          #+#    #+#             */
/*   Updated: 2026/02/09 13:03:31 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OUTPUTS_H
# define OUTPUTS_H

# include "enums.h"

/**
 * @brief Display an error on the stderr
 * @param error The error message to display
 * @return Returns 0 on success, 1 on failure
 */
t_status	error_output(const char *error);

#endif