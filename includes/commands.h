/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:13:55 by juperrin          #+#    #+#             */
/*   Updated: 2026/02/12 08:02:19 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include "definitions.h"

/**
 * @brief Execute the command line passed in.
 * @param command The command to execute.
 * @param input_fd File descriptor to redirect the stdin. -1 to not redirect.
 * @param output_file File descriptor to redirect the stdout. -1 to not redirect.
 * @return Nothing on success, the execve error code otherwise.
 */
int			exec(char *command, int input_fd, int output_fd);

/**
 * @brief Displays the current working directory.
 */
t_status	pwd(void);

/**
 * @brief Change the current directory
 */
t_status	cd(const char *path);

#endif
