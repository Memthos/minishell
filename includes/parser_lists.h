/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lists.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memthos </var/spool/mail/memthos>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 22:05:37 by memthos           #+#    #+#             */
/*   Updated: 2026/04/17 22:20:18 by memthos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_LISTS_H
# define PARSER_LISTS_H

# include "types.h"

typedef struct s_lxr_lst
{
	char				*data;
	t_token				token;
	long				p_dpt;
	struct s_lxr_lst	*next;
}						t_lxr_lst;

typedef struct s_ast_lst
{
	char				*data;
	t_token				token;
	t_expand			expand_state;
	struct s_ast_lst	*left;
	struct s_ast_lst	*right;
}						t_ast_lst;

typedef struct s_char_lst
{
	char				*data;
	struct s_char_lst	*next;
}						t_char_lst;

typedef struct s_cmd_lst
{
	t_ast_lst			*ast;
	struct s_cmd_lst	*next;
}						t_cmd_lst;

#endif
