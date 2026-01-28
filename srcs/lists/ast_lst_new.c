/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_lst_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 11:09:00 by juperrin          #+#    #+#             */
/*   Updated: 2026/01/28 23:09:31 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast_lst	*ast_lst_new(char *data, t_token token, size_t p_dpt)
{
	t_ast_lst	*new;

	new = (t_ast_lst *)malloc(sizeof(t_ast_lst));
	if (NULL == new)
		return (NULL); //ADD FREE FOR LEXER ETC.
	new->data = data;
	new->token = token;
	new->p_dpt = p_dpt;
	new->left = NULL;
	new->right = NULL;
	return (new);
}
