/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 11:12:03 by juperrin          #+#    #+#             */
/*   Updated: 2026/01/22 11:12:46 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef enum e_TOKENS
{
	S_QUOTE,
	D_QUOTE,
	RED_IN,
	RED_OUT_REP,
	RED_OUT_APP,
	DELIMITER,
	PIPE,
	ENV_VAR,
	COMMAND,
	CMD_ARG,
}	t_token;

#endif