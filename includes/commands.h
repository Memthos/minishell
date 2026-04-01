/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:13:55 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/01 17:51:54 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include "definitions.h"

# define CMD_COUNT 7

typedef struct s_shell	t_shell;

typedef t_status		(*t_built_in)(char **, t_shell *);

typedef struct s_command
{
	char		*name;
	t_status	(*cmd)(char **, t_shell *);
}	t_command;

/**
 * @brief If name is in the built in list, gets the corresponding function,
 * get cmd_exec otherwise.
 * @param name The command name to get.
 * @return A function pointer to the right command to execute,
 * NULL if name is NULL.
 */
t_built_in	get_command(char *name);

/**
 * @brief Runs the command contains in shell->cur_cmd in a child process.
 */
t_status	run_comand(t_shell *shell);

/**
 * @brief Execute a command with execve.
 * @param args The command and its arguments.
 * @param env The global shell structure.
 * @return Nothing on success, 1 on failure.
 */
t_status	cmd_exec(char **args, t_shell *shell);

/**
 * @brief Writes a message on the standard output.
 * @param args The command and its arguments.
 * @param env The global shell structure.
 * @return Always returns 0.
 */
t_status	cmd_echo(char **args, t_shell *shell);

/**
 * @brief Displays the current working directory using get_cwd function.
 * @param args The command and its arguments.
 * @param env The global shell structure.
 * @return 0 on success, 1 on failure.
 */
t_status	cmd_pwd(char **args, t_shell *shell);

/**
 * @brief Returns the current working directory based first on PWD env variable,
 * and the getcwd func if PWD is not set.
 * @return The allocated current working directory.
 */
char		*get_cwd(t_shell *shell);

/**
 * @brief Change the current working directory
 * @param args The command and its arguments.
 * @param env The global shell structure.
 * @return 0 on success, 1 on failure.
 */
t_status	cmd_cd(char **args, t_shell *shell);

/**
 * @brief Prints all the environments variables.
 * @param args The command and its arguments.
 * @param env The global shell structure.
 * @return Always return 0, except if env is NULL.
 */
t_status	cmd_env(char **args, t_shell *shell);

/**
 * @brief Adds an environment variable to the current environment.
 * @param args The command and its arguments.
 * @param env The global shell structure.
 * @return 0 on success, 1 on failure.
 */
t_status	cmd_export(char **args, t_shell *shell);

/**
 * @brief Removes an environment variable.
 * @param args The command and its arguments.
 * @param env The global shell structure.
 * @return Always return 0.
 */
t_status	cmd_unset(char **args, t_shell *shell);

/**
 * @brief Exit the program.
 * @param args The command and its arguments.
 * @param env The global shell structure.
 * @return Return 0 or any code passed as an argument or 2 on bad argument.
 */
t_status	cmd_exit(char **args, t_shell *shell);

/// @brief Get the heredoc input from the user.
/// @param shell A pointer to the the shell structure.
/// @return 1 if an error occurred, else 0.
int			heredoc(t_shell *shell, t_ast_lst *node);

#endif
