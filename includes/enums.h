/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 11:12:03 by juperrin          #+#    #+#             */
/*   Updated: 2026/01/24 05:30:54 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUMS_H
# define ENUMS_H

typedef enum e_return_status
{
	SUCCESS,
	FAILURE,
}	t_status;

typedef enum e_quote_t
{
	S_QUOTE = 1,
	D_QUOTE = 2,
}	t_quote_t;

typedef enum e_tokens
{
	ASSIGNMENT_W,
	AND_IF,
	OR_IF,
	DLESS,
	DGREAT,
	LESS,
	GREAT,
	PIPE,
	WORD,
}	t_token;

#endif
