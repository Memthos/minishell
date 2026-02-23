/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definitions.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:47:24 by juperrin          #+#    #+#             */
/*   Updated: 2026/02/23 10:49:09 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINITIONS_H
# define DEFINITIONS_H

typedef unsigned int	t_uint;
typedef unsigned char	t_uint8;

typedef enum e_return_status
{
	SUCCESS,
	FAILURE,
	BAD_ARG,
	PIPE_FAILURE,
	FORK_FAILURE,
	DUP_FAILURE,
	OVERFLOW,
	UNDERFLOW,
}	t_status;

typedef enum e_quote_t
{
	S_QUOTE = 1,
	D_QUOTE = 2,
}	t_quote_t;

typedef enum e_tokens
{
	TOKEN,
	NEW_LINE,
	ASSIGNMENT_W,
	AND_IF,
	OR_IF,
	DLESS,
	DGREAT,
	LESS,
	GREAT,
	PIPE,
	WORD,
	IO_NUMBER,
	L_PAREN,
	R_PAREN,
	CMP_CMD,
	WILDCARD,
	END_OF_INPUT,
}	t_token;

#endif