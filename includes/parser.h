/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:50:51 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/16 15:37:56 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lists.h"
# include "shell.h"

/// @brief Function tp expand params in user input.
/// @param node The node with the data to expand.
/// @param status The status of the parser.
/// @param dict A reference to the dictionary storing all the env variables.
void		expand(t_ast_lst *node, t_status *status, t_dictionary *dict);

/**
 * @brief First step of parsing, apply a token to each part
 * of the string by separating them.
 * @param lxr A pointer to the head of the list.
 * @param s The string written as input.
 * @return Return 1 if an error occurred, else 0.
 */
void		lexer(t_lxr_lst **lxr, char *s, t_status *status);

/// @brief The main function of the parser.
/// @param s The line written by the user.
/// @return The status of the parser
t_status	parser(char *s, t_shell *shell);

/**
 * @brief Return a new string of len size from input.
 * @param input The original string.
 * @param len the wanted size of the returned string.
 * @return The newly created string.
 */
char		*make_str(char *input, size_t len);

/// @brief Check if the lexer has unclosed quotes or wrong parenthesis.
/// @param lxr A pointer to the head of the lexer.
/// @param status The status of the parser.
void		checker_lxr(t_lxr_lst *lxr, t_status *status);

/**
 * @brief Update the quote state depending of the given character.
 * @param quote A pointer to the quote state.
 * @param c The currently looked at character.
 * @return Returns 1 one the state changed, else 0.
 */
int			set_quote_state(t_quote_t *quote, char c);

/// @brief Set the finals token so the lexer nodes are correct.
/// @param lxr A pointer to the head of the lexer.
void		set_final_tokens(t_lxr_lst *lxr);

/// @brief Remove the unnecessary quotes for the date of each lexer node.
/// @param lxr A pointer to the head of the lexer.
/// @param status The status of the parser.
/// @return 1 If an error happened, else 0.
void		update_quotes(t_ast_lst *ast, t_status *status);

/// @brief Make the base of the AST tree, calls all the other functions
/// of the ast.
/// @param lxr A node pointing to the currently looked at token.
/// @param status The status of the parser.
/// @return The newly created ast tree.
t_ast_lst	*complete_command_r(t_lxr_lst **lxr, t_status *status);

/// @brief Make a part of the ast for the and_or rule.
/// @param lxr A pointer to the current node of lxr.
/// @param status The status of the parser.
/// @return The newly created part of the ast tree.
t_ast_lst	*and_or_r(t_lxr_lst **lxr, t_status *status);

/// @brief Return the head pointer of a compound command.
/// @param lxr The pointer to the current node of lxr.
/// @param status The status of the parser.
/// @return The newly created ast tree.
t_ast_lst	*compound_cmd_r(t_lxr_lst **lxr, t_status *status);

/// @brief Return the head pointer if an io redirect loop.
/// @param lxr The pointer to the current node of lxr.
/// @param status The status of the parser.
/// @return The newly created ast tree.
t_ast_lst	*redirect_loop(t_lxr_lst **lxr, t_status *status);

/// @brief Make an ast tree for a command, either a compound or a simple one.
/// @param lxr A node pointing to the currently looked at token.
/// @param status The status of the parser.
/// @return The newly created ast tree.
t_ast_lst	*command_r(t_lxr_lst **lxr, t_status *status);

/// @brief Create an a small ast tree with an io_redirect cmd.
/// @param lxr A pointer to the currently looked at lexer node.
/// @param status The status of the parser.
/// @param side Side of create the redirect tree, left or right.
/// @return Return a redirect_io ast tree.
t_ast_lst	*io_redirect_r(t_lxr_lst **lxr, t_status *status, t_side side);

/// @brief Check if the given node can be of redirect type
/// @param lxr A pointer to the given node
int			is_io_redirect(t_lxr_lst **lxr);

#endif
