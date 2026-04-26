/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:13:55 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/26 17:32:38 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include "types.h"

# define CMD_COUNT 7

typedef struct s_shell	t_shell;

typedef t_status		(*t_built_in)(t_strings , t_shell *);

typedef struct s_command
{
	t_string	name;
	t_status	(*cmd)(t_strings, t_shell *);
}	t_command;

/**
 * @brief If name is in the built in list, gets the corresponding function,
 * get cmd_exec otherwise.
 * @param name The command name to get.
 * @return A function pointer to the right command to execute,
 * NULL if name is NULL.
 */
t_built_in	get_command(t_string name);

/**
 * @brief Execute a command with execve.
 * @param args The command and its arguments.
 * @param env The global shell structure.
 * @return Nothing on success, 1 on failure.
 */
t_status	cmd_exec(t_strings args, t_shell *shell);

/**
 * @brief Writes a message on the standard output.
 * @param args The command and its arguments.
 * @param env The global shell structure.
 * @return Always returns 0.
 */
t_status	cmd_echo(t_strings args, t_shell *shell);

/**
 * @brief Displays the current working directory using get_cwd function.
 * @param args The command and its arguments.
 * @param env The global shell structure.
 * @return 0 on success, 1 on failure.
 */
t_status	cmd_pwd(t_strings args, t_shell *shell);

/**
 * @brief Returns the current working directory based first on PWD env variable,
 * and the getcwd func if PWD is not set.
 * @return The allocated current working directory.
 */
t_string	get_cwd(t_shell *shell);

/**
 * @brief Change the current working directory
 * @param args The command and its arguments.
 * @param env The global shell structure.
 * @return 0 on success, 1 on failure.
 */
t_status	cmd_cd(t_strings args, t_shell *shell);

/**
 * @brief Prints all the environments variables.
 * @param args The command and its arguments.
 * @param env The global shell structure.
 * @return Always return 0, except if env is NULL.
 */
t_status	cmd_env(t_strings args, t_shell *shell);

/**
 * @brief Adds an environment variable to the current environment.
 * @param args The command and its arguments.
 * @param env The global shell structure.
 * @return 0 on success, 1 on failure.
 */
t_status	cmd_export(t_strings args, t_shell *shell);

/**
 * @brief Removes an environment variable.
 * @param args The command and its arguments.
 * @param env The global shell structure.
 * @return Always return 0.
 */
t_status	cmd_unset(t_strings args, t_shell *shell);

/**
 * @brief Exit the program.
 * @param args The command and its arguments.
 * @param env The global shell structure.
 * @return Return 0 or any code passed as an argument or 2 on bad argument.
 */
t_status	cmd_exit(t_strings args, t_shell *shell);

#endif
