/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:50:51 by mperrine          #+#    #+#             */
/*   Updated: 2026/02/20 13:43:56 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lists.h"

/**
 * @brief First step of parsing, apply a token to each part
 * of the string by separating them.
 * @param lxr A pointer to the head of the list.
 * @param s The string written as input.
 * @return Return 1 if an error occurred, else 0.
 */
int			lexer(t_lxr_lst **lxr, char *s);

/// @brief The main function of the parser.
/// @param s The line written by the user.
/// @return The ast tree.
t_ast_lst	*parser(char *s);

/**
 * @brief Return a new string of len size from input.
 * @param input The original string.
 * @param len the wanted size of the returned string.
 * @return The newly created string.
 */
char		*make_str(char *input, size_t len);

/**
 * @brief Return true if the quote state changed.
 * @param state A pointer to the quote state.
 * @param p A pointer to the lexer params.
 * @return 1 if the quote state changed else 0.
 */
int			check_quote(t_lxr_p *p, char c);

/// @brief Set the finals token so the lexer nodes are correct.
/// @param lxr A pointer to the head of the lexer.
void		set_final_tokens(t_lxr_lst *lxr);

/// @brief Make the base of the AST tree, calls all the other functions
/// of the ast.
/// @param lxr A node pointing to the currently looked at token.
/// @return The newly created ast tree.
t_ast_lst	*complete_command_r(t_lxr_lst **lxr);

/// @brief Make a part of the ast for the and_or rule.
/// @param lxr A pointer to the current node of lxr.
/// @param ret A pointer to an integer to know if there an error.
/// @return The newly created part of the ast tree.
t_ast_lst	*and_or_r(t_lxr_lst **lxr, int *ret);

/// @brief Return the head pointer of a compound command.
/// @param lxr The pointer to the current node of lxr.
/// @param ret A pointer to an integer to know if there an error.
/// @return The newly created ast tree.
t_ast_lst	*compound_cmd_r(t_lxr_lst **lxr, int *ret);

/// @brief Return the head pointer if an io redirect loop.
/// @param lxr The pointer to the current node of lxr.
/// @param ret A pointer to an integer to know if there an error.
/// @return The newly created ast tree.
t_ast_lst	*redirect_loop(t_lxr_lst **lxr, int *ret);

/// @brief Make an ast node for a simple command and consume the lexer.
/// @param lxr A node pointing to the currently looked at token.
/// @param ret A pointer to an integer to know if there an error.
/// @return The newly created ast node.
t_ast_lst	*simple_command_r(t_lxr_lst **lxr, int *ret);

/// @brief Create an a small ast tree with an io_redirect cmd.
/// @param lxr A pointer to the currently looked at lexer node.
/// @param ret A pointer to an integer to know if there an error.
/// @return Return a redirect_io ast tree.
t_ast_lst	*io_redirect_r(t_lxr_lst **lxr, int *ret);

/// @brief Check if the given node can be of redirect type
/// @param lxr A pointer to the given node
int			is_io_redirect(t_lxr_lst **lxr);

#endif
