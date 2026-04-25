/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 21:08:08 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/25 16:08:15 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

/**
 * @brief Redirects standard input to fd.
 */
t_status	redirect_input(int *fd);

/**
 * @brief Redirects standard output to fd.
 */
t_status	redirect_output(int *fd);
