/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:50:51 by mperrine          #+#    #+#             */
/*   Updated: 2026/04/26 16:30:45 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lists.h"
# include "shell.h"

/// @brief Function to expand params in user input.
/// @param node The node with the data to expand.
/// @param status The status of the parser.
/// @param shell A reference to the variables of the shell.
/// @param is_red Param to check whether or not the node is the WORD of
/// a redirection.
void		expand(t_ast_lst **node, t_status *status, t_shell *sh, int is_red);

/// @brief Special expand for the heredoc.
/// @param str The string to expand.
/// @param shell A reference to the variables of the shell.
/// @return The exit status of the expander.
t_status	expand_heredoc(t_strings str, t_shell *shell);

/// @brief Function to expand the given data.
/// @param data THe data to expand.
/// @param data_i The current index in the data.
/// @param shell A pointer to the shell struct.
/// @param is_red Param to check whether or not the node is the WORD of
/// a redirection.
/// @return The exit status of the function
t_status	expand_node(t_strings data, size_t *idx, t_shell *sh, int is_red);

/// @brief Check whether or not an expand can happen from the current character.
/// @param str The string to check.
/// @param i THe index to start checking from.
/// @param quote_state THe current quote state.
/// @return Return 1 if the data can be expanded, else 0.
int			can_expand(char *str, size_t i, t_quote_t quote_state);

/// @brief Function to check if the node data can try to be expanded
/// @param node The node with the data to expand.
/// @param status The status of the parser.
/// @param shell A reference to the variables of the shell.
/// @return 1 if the data can be expanded, else 0.
int			can_try_expand(t_ast_lst *node, t_status *status, t_shell *shell);

/// @brief Search a value for the expand variable name.
/// @param var_name The name of the expand variable to search for.
/// @param shell A reference to the variables of the shell.
/// @return Either the variable value or NULL if nothing was found.
t_string	get_expand_value(t_string var_name, t_shell *sh, t_status *status);

/// @brief Get the name of the variable to expand.
/// @param s The base string.
/// @param name A pointer to the string that will contain the node.
/// @param i The index where a $ was found.
/// @return 1 if there was an allocation failure, else 0.
int			get_var_name(t_string s, t_strings name);

/// @brief Check whether or not the node is the WORD of a redirection
/// @param node THe node to check
/// @return 1 if True, else 0.
int			is_redirection(t_ast_lst *node);

/// @brief Convert a newly expanded value to an ast to merge to the
/// original one.
/// @param lxr The lexer to parse.
/// @param ast THe original ast.
/// @return The status of the parser.
t_status	expand_to_ast(t_lxr_lst **lxr, t_ast_lst *ast);

/// @brief Function to get the number of quotes to remove the the given node.
/// @param node A pointer to the ast node.
/// @return The number of quotes tu return, 0 if ne given node is NULL.
size_t		get_quotes_rmv(t_ast_lst *node);

/**
 * @brief First step of parsing, apply a token to each part
 * of the string by separating them.
 * @param lxr A pointer to the head of the list.
 * @param s The string written as input.
 * @return Return 1 if an error occurred, else 0.
 */
void		lexer(t_lxr_lst **lxr, t_string s, t_status *status);

/// @brief The main function of the parser.
/// @param s The line written by the user.
/// @return The status of the parser
t_status	parser(t_string s, t_shell *shell);

/// @brief The final step of the parsing, it makes the expand,
/// set the wildcards and removes the quotes.
/// @param shell A reference to the variables of the shell.
/// @param ast A pointer to the ast.
/// @return The exit status.
t_status	final_parsing(t_shell *shell, t_ast_lst **ast);

/**
 * @brief Return a new string of len size from input.
 * @param input The original string.
 * @param len the wanted size of the returned string.
 * @return The newly created string.
 */
t_string	make_str(t_string input, size_t len);

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

/// @brief Remove the nb of quotes from the given node.
/// @param ast A pointer to the ast node.
/// @param quotes_rmv The number of quotes to remove
/// @return The status of the parser.
t_status	remove_quotes(t_ast_lst *ast, size_t quotes_rmv);

/// @brief Remove the quotes of the given node.
/// @param ast A pointer to the ast node.
/// @param status The status of the parser.
void		remove_node_quotes(t_ast_lst **ast, t_status *status);

/// @brief Remove the unnecessary quotes for the date of each lexer node.
/// @param ast A pointer to the head of the ast.
/// @param status The status of the parser.
void		remove_ast_quotes(t_ast_lst **ast, t_status *status);

/// @brief Search for wildcards if necessary and add them to the ast.
/// @param ast A pointer to the head of the ast.
/// @param status The status of the parser.
/// @param is_red Param to check whether or not the node is the WORD of
/// a redirection.
void		wildcards(t_ast_lst *node, t_status *status, int is_red);

/// @brief Remove the lost wildcards if there is a / in the data
/// @param node The node to parse.
/// @return THe status of the parsing.
t_status	remove_wildcard(t_ast_lst *node);

/// @brief Function that remove files that don't respect the wildcard model.
/// @param files The list of files.
/// @param model THe model to respect.
void		filter_files(t_char_lst **files, t_string model);

/// @brief Function to list all the files and directories from the current one
/// @param status The status of the parser.
/// @return A chained list with all the files that were found.
/// @param THe model for the wildcard.
t_char_lst	*get_files(t_status *status, char *model);

/// @brief Make the base of the AST tree, calls all the other functions
/// of the ast.
/// @param lxr A node pointing to the currently looked at token.
/// @param shell A pointer to the main structure of minishell.
/// @param status The status of the parser.
void		complete_command_r(t_lxr_lst **lxr, t_shell *shell,
				t_status *status);

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

/// @brief Check if the given tree contains a here_doc redirection.
/// @param red The given tree.
/// @param side THe side to move on.
/// @return 1 if a here_doc was found, else 0.
int			is_heredoc(t_ast_lst *red, t_side side);

/// @brief Check if the limiter of the heredoc has quotes.
/// @param red Redirection tree.
/// @param side SIde to search.
/// @return 1 if a quote was found or the limiter is NULL, else 0.
int			limiter_quotes(t_ast_lst *red, t_side side);

#endif
