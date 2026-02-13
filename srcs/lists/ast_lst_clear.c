/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_lst_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 10:07:53 by mperrine          #+#    #+#             */
/*   Updated: 2026/02/13 09:45:42 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ast_lst_clear(t_ast_lst **head)
{
	if (NULL == head || NULL == *head)
		return ;
	if ((*head)->left)
		ast_lst_clear(&(*head)->left);
	if ((*head)->right)
		ast_lst_clear(&(*head)->right);
	free((*head)->data);
	free(*head);
	*head = NULL;
}
