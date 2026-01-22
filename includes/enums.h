/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 11:12:03 by juperrin          #+#    #+#             */
/*   Updated: 2026/01/22 14:15:18 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef enum e_return_status
{
	SUCCESS,
	FAILURE,
}	t_status;

typedef enum e_tokens
{
	WORD,
	ASSIGNMENT_WORD,
	NAME,
	NEW_LINE,
	IO_NUMBER,
	AND_IF,
	OR_IF,
	DLESS,
	DGREAT,
	LESSGREAT,
}	t_token;

#endif
