/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 11:29:36 by juperrin          #+#    #+#             */
/*   Updated: 2026/02/20 18:45:21 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "enums.h"

/**
 * @brief Try to get the first number contained in S and set NUMBER to it.
 * @param s The string from which you wanna get a number.
 * @param number A pointer to a number that will contains the result.
 * @return A status to tell if the number has been successfully parsed or not.
 */
t_status	get_number(const char *s, int *number);

/**
 * @brief Splits a string into two separates allocated strings.
 * @return Always returns an array that contains two strings.
 */
char		**split_at(const char *str, const char c);

/**
 * @brief Returns the number of words in str.
 * @param str The string where to count words.
 * @param set The character set that contains delimiters.
 * @return The number of words in str.
 */
t_uint		count_words(const char *str, const char *set);

void		free_strings(char **strs);

bool	check_var_name(char *name);

void	swap_str(char **a, char **b);

#endif
