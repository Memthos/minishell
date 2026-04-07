/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 14:38:19 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/07 14:26:56 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "types.h"
# include "lists.h"

/**
 * @brief Executes all necessary things to do in the command ast.
 */
t_status	execute(t_ast_lst *cmd, t_shell *shell);

/**
 * @brief Executes the command contained in cur_cmd.
 */
t_status	execute_cmd(t_shell *shell);

#endif