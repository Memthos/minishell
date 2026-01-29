/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 11:29:36 by juperrin          #+#    #+#             */
/*   Updated: 2026/01/29 11:24:07 by mperrine         ###   ########.fr       */
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


/// @brief Copy s and free it after copying it in a newly allocated block of memory.
/// @param s The string to copy.
/// @return The newly created string.
char	*ft_strcpy(char *s);

/// @brief Concatenate s2 to s1 and separate them with sep.
/// @param s1 The address of the string to concatenate
/// @param s2 The string to add to s1.
void	ft_strjoin_sep(char **s1, const char *s2, char sep);

#endif
