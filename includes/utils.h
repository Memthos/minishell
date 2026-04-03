/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 11:29:36 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/03 21:10:59 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "definitions.h"

/**
 * @brief Trys to get the first number contained in S and set NUMBER to it.
 * @param s The string from which you wanna get a number.
 * @param number A pointer to a number that will contains the result.
 * @return A status to tell if the number has been successfully parsed or not.
 */
t_status		get_number(const char *s, int *number);

/**
 * @brief Splits a string into two separates allocated strings.
 * @return Always returns an array that contains two strings.
 */
char			**split_at(const char *str, const char c);

/**
 * @brief Returns the number of words in str.
 * @param str The string where to count words.
 * @param set The character set that contains delimiters.
 * @return The number of words in str.
 */
t_uint			count_words(const char *str, const char *set);

/**
 * @brief Frees each arrays in strs and strs itself.
 */
void			free_strings(char **strs);

/**
 * @brief Checks if a variable name is correct.
 * @return true on if name is correct, false otherwise.
 */
bool			check_var_name(char *name);

/**
 * @brief Swaps a and b.
 */
void			swap_str(char **a, char **b);

/**
 * @brief Checks if str contains only digits.
 * @return true on success, false on failure.
 */
bool			str_is_digit(char *str);

/**
 * @brief Checks if str is empty or not.
 */
bool			str_is_empty(char *str);

/// @brief Checks whether or not the input string contains spaces, tabs, etc.
/// @param str The string to check
/// @return 1 if True, else 0.
int				contain_space(char *str);

/**
 * @brief Reallocs array to add memory for one more element.
 * array have to be NULL if count is 0.
 * @param array The array to realloc.
 * @param count The current number of elements in array.
 * @param size The size of the one element of array.
 * @return A new array with the updated size.
 *
 */
void			*increment_array(void *array, t_uint count, t_uint size);

/**
 * @brief Closes the fd passed in and set its value to -1.
 * Does nothing if fd < 0.
 */
int				ft_close(int *fd);

/**
 * @brief Checks if the PATH environment variable looks correct.
 * @return True on success, false on failure.
 */
bool			check_path(t_shell *shell);

/**
 * @brief Updates the SHLVL environment variable value.
 * @return The updated environment.
 */
t_dictionary	*update_shlvl(t_dictionary **env);

#endif
