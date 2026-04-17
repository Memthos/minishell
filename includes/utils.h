/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 11:29:36 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/17 11:06:18 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "types.h"

/**
 * @brief Swaps pointers a and b.
 */
void			swap_ptr(void **a, void **b);

/**
 * @brief Trys to get the first number contained in S and set NUMBER to it.
 * @param s The t_string from which you wanna get a number.
 * @param number A pointer to a number that will contains the result.
 * @return A status to tell if the number has been successfully parsed or not.
 */
t_status		get_number(const t_string s, int *number);

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
 * @brief Splits a t_string into two separates allocated t_strings.
 * @return Always returns an array that contains two t_strings.
 */
char			**split_at(const t_string str, const char c);

/**
 * @brief Returns the number of t_string in a t_string array.
 */
t_uint			t_strings_size(const t_strings strs);

/**
 * @brief Frees each arrays in strs and strs itself.
 */
void			free_t_strings(t_strings strs);

/**
 * @brief Checks if a variable name is correct.
 * @return true on if name is correct, false otherwise.
 */
bool			check_var_name(t_string name);

/**
 * @brief Checks if str contains only digits.
 * @return true on success, false on failure.
 */
bool			str_is_digit(t_string str);

/**
 * @brief Checks if str is empty or not.
 */
bool			str_is_empty(t_string str);

/// @brief Checks whether or not the input t_string contains spaces, tabs, etc.
/// @param str The t_string to check
/// @return 1 if True, else 0.
bool			contain_space(t_string str);

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

/**
 * @brief Returns true if path is a directory, false otherwise.
 */
bool			is_dir(const t_string path);

#endif
