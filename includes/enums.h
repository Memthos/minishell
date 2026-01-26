/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 11:12:03 by juperrin          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2026/01/26 15:48:12 by mperrine         ###   ########.fr       */
=======
/*   Updated: 2026/01/26 14:59:36 by juperrin         ###   ########.fr       */
>>>>>>> 2086ba73a2cd799f2c8b55ac0d29d4e40252d0b1
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUMS_H
# define ENUMS_H

typedef enum e_return_status
{
	SUCCESS,
	FAILURE,
	OVERFLOW,
	UNDERFLOW,
	PWD_ERROR,
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
	L_PAREN,
	R_PAREN,
	WORD,
	IO_NUMBER,
}	t_token;

#endif
