/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 11:10:37 by juperrin          #+#    #+#             */
/*   Updated: 2026/02/20 08:14:37 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DICTIONARY_H
# define DICTIONARY_H

# include "definitions.h"

typedef struct s_dictionary
{
	char				*key;
	void				*data;
	struct s_dictionary	*next;
}						t_dictionary;
/**
 * @brief Creates a new dictionary.
 * @param key The unique key to access the new data.
 * @param data The new data to store.
 * @return The allocated dict on success. NULL on failure.
 */
t_dictionary	*dict_new(char *key, void *data);

/**
 * @brief Adds a new entry to the dictionary passed in.
 * @param dict The dictionary where to add the new entry.
 * @param key The unique key to access the new data.
 * @param data The new data to store.
 * @return The same dictionary with the new entry on success. NULL on failure.
 */
t_dictionary	*dict_add(t_dictionary **dict, char *key, void *data);

/**
 * @brief Returns a entry based on the key passed in.
 * @param dict The dictionary to search in.
 * @param key The unique key to retrieve the entry.
 * @return The dictionary entry on success, NULL on failure.
 */
t_dictionary	*dict_get(t_dictionary *dict, char *key);

/**
 * @brief Updates an entry in the dictionary passed in.
 * @param dict The dictionary where the entry to update is.
 * @param key The entry unique key.
 * @param data The new data.
 * @return The dictionary on success, NULL on failure.
 */
t_dictionary	*dict_update(t_dictionary *dict, char *key, void *data);

/**
 * @brief Removes an entry based on the given key.
 * @param dict The dictionary where to remove the entry.
 * @param key The unique key to remove the wanted entry.
 * @return The same dictionary without the removed entry.
 */
t_dictionary	*dict_remove(t_dictionary **dict, char *key);

/**
 * @brief Clear the dictionary passed in.
 * @param dict The dictionary to clear.
 */
void			dict_clear(t_dictionary **dict);

/**
 * @brief Gives the size of a dictionary.
 * @return The number of entries in a dictionary.
 */
t_uint	dict_size(t_dictionary *dict);

/**
 * @brief Transforms a dictionary into a string array.
 * @param dict The dictionary to transform.
 * @param sep The separation character to add between the key and the value.
 * @return An allocated string array that contains all the keys and their values.
 */
char	**dict_to_array(t_dictionary *dict, char sep);

/**
 * @brief For debug purposes, prints all the key with their assigned values
 */
void	dict_display(t_dictionary *dict);

#endif