/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_lst_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 10:07:53 by mperrine          #+#    #+#             */
/*   Updated: 2026/02/20 12:53:50 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ast_lst_clear(t_ast_lst **head)
{
	if (!head || !*head)
		return ;
	if ((*head)->left)
		ast_lst_clear(&(*head)->left);
	if ((*head)->right)
		ast_lst_clear(&(*head)->right);
	if ((*head)->data)
		free((*head)->data);
	free(*head);
	*head = NULL;
}
