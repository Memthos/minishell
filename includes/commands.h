/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:13:55 by juperrin          #+#    #+#             */
/*   Updated: 2026/02/19 08:59:03 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include "definitions.h"
#include "dictionary.h"

/**
 * @brief Execute the command line passed in.
 * @param command The command to execute.
 * @param input_fd File descriptor to redirect the stdin. -1 to not redirect.
 * @param output_file File descriptor to redirect the stdout. -1 to not redirect.
 * @return Nothing on success, the execve error code otherwise.
 */
int			exec(char *command, int input_fd, int output_fd);

/**
 * @brief Writes a message on the stdout.
 * @param msg Ths message to write.
 * @param line_break If 1(true) adds a line break after the message.
 * @return 0 on success, 1 on failure.
 */
t_status	ft_echo(char *msg, t_uint8 line_break);

/**
 * @brief Displays the current working directory.
 */
t_status	pwd(void);

/**
 * @brief Change the current directory
 * @param path The path where to change the current directory.
 * @return 0 on success, 1 on failure.
 */
t_status	cd(const char *path);

/**
 * @brief Prints all the environments variables.
 * @param env The environment dictionary.
 */
void	env(t_dictionary *env);

/**
 * @brief Adds an environment variable to the current environment.
 * @param env The current environment.
 * @param name The entry unique name/key.
 * @param value The entry content.
 * @param concatenate Concatenate 'value' with the current name value if existing.
 * @return 0 on success, 1 on failure.
 */
t_status	export(t_dictionary **env, char *name, char *value, bool concatenate);


/**
 * @brief Removes the 'name' environment variable.
 * @param env The environment dictionary.
 * @param name The environment variable to remove.
 * @return 0 on success, 1 on failure.
 */
t_status	unset(t_dictionary **env, char *name);

#endif
