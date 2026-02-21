/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:13:55 by juperrin          #+#    #+#             */
/*   Updated: 2026/02/21 11:31:33 by juperrin         ###   ########.fr       */
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
 * @brief Writes a message on the standard output.
 * @param args The command arguments.
 * @param env The shell environment.
 * @return Always returns 0.
 */
t_status	cmd_echo(char **args, t_dictionary **env);

/**
 * @brief Displays the current working directory.
 * @param args The command arguments.
 * @param env The shell environment.
 * @return 0 on success, 1 on failure.
 */
t_status	cmd_pwd(char **args, t_dictionary **env);

/**
 * @brief Change the current working directory
 * @param args The command arguments.
 * @param env The shell environment.
 * @return 0 on success, 1 on failure.
 */
t_status	cmd_cd(char **args, t_dictionary **env);

/**
 * @brief Prints all the environments variables.
 * @param args The command arguments.
 * @param env The environment dictionary.
 * @return Always return 0, except if env is NULL.
 */
t_status	cmd_env(char **args, t_dictionary **env);

/**
 * @brief Adds an environment variable to the current environment.
 * @param args The command arguments.
 * @param env The environment dictionary.
 * @return 0 on success, 1 on failure.
 */
t_status	cmd_export(char **args, t_dictionary **env);


/**
 * @brief Removes an environment variable.
 * @param args The command arguments.
 * @param env The environment dictionary.
 * @return Always return 0.
 */
t_status	cmd_unset(char **args, t_dictionary **env);

#endif
