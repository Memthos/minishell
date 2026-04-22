/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lists.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 22:05:37 by memthos           #+#    #+#             */
/*   Updated: 2026/04/23 01:43:04 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_LISTS_H
# define PARSER_LISTS_H

# include "types.h"

typedef struct s_lxr_lst
{
	t_string			data;
	t_token				token;
	long				p_dpt;
	struct s_lxr_lst	*next;
}						t_lxr_lst;

typedef struct s_ast_lst
{
	t_string			data;
	t_token				token;
	t_expand			expand_state;
	struct s_ast_lst	*left;
	struct s_ast_lst	*right;
}						t_ast_lst;

typedef struct s_char_lst
{
	t_string			data;
	struct s_char_lst	*next;
}						t_char_lst;

typedef struct s_cmd_lst
{
	t_ast_lst			*ast;
	struct s_cmd_lst	*next;
}						t_cmd_lst;

#endif
