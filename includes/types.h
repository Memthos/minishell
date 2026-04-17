/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 14:27:08 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/17 11:06:18 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

typedef unsigned int	t_uint;
typedef unsigned char	t_uint8;

typedef char*			t_string;
typedef char**			t_strings;

typedef enum e_return_status
{
	NO_ERR_MSG = -1,
	SUCCESS,
	FAILURE,
	BAD_ARG,
	TOO_MUCH_ARG,
	OVERFLOW,
	UNDERFLOW,
	ALLOCATION_FAILURE,
	EXECVE_FAILURE,
	PIPE_FAILURE,
	FORK_FAILURE,
	DUP_FAILURE,
	OPEN_FAILURE,
	FILE_NOT_FOUND,
	PERMISSION_ERROR,
	COMMAND_NOT_FOUND,
	IS_DIRECTORY,
	HEREDOC_COUNT_EXCEEDED,
	READDIR_FAILURE,
	NUM_ARG_REQUIRED,
}	t_status;

typedef enum e_quote_t
{
	NONE,
	S_QUOTE,
	D_QUOTE,
}	t_quote_t;

typedef enum e_side
{
	LEFT,
	RIGHT,
}	t_side;

typedef enum e_expand
{
	DENY,
	ALLOW,
	HEREDOC_DENY,
	HEREDOC_ALLOW,
}	t_expand;

typedef enum e_tokens
{
	TOKEN,
	NEW_LINE,
	AND_IF,
	OR_IF,
	DLESS,
	DGREAT,
	LESS,
	GREAT,
	PIPE,
	WORD,
	L_PAREN,
	R_PAREN,
	CMP_CMD,
	WILDCARD,
}	t_token;

#endif
