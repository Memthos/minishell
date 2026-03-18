/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definitions.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:47:24 by juperrin          #+#    #+#             */
/*   Updated: 2026/03/18 15:11:30 by mperrine         ###   ########.fr       */
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
	ALLOCATION_FAILURE,
	ASSIGN_FAILURE,
	EXECVE_FAILURE,
	PIPE_FAILURE,
	FORK_FAILURE,
	DUP_FAILURE,
	OPEN_FAILURE,
	OVERFLOW,
	UNDERFLOW,
	PARENTHESIS_FAILURE,
	QUOTES_FAILURE,
	REDIRECTION_FAILURE,
	OPERATOR_FAILURE,
	WILDCARD_FAILURE,
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
	IO_NUMBER,
	L_PAREN,
	R_PAREN,
	CMP_CMD,
	WILDCARD,
	END_OF_INPUT,
}	t_token;

#endif
