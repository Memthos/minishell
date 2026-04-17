/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_lst_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 10:07:53 by mperrine          #+#    #+#             */
/*   Updated: 2026/04/17 11:35:46 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_ast_lst	*ast_lst_pop(t_ast_lst **node)
{
	t_ast_lst	*new_next;

	if (!node || !*node)
		return (NULL);
	if ((*node)->left)
		ast_lst_clear(&(*node)->left);
	if (!(*node)->right)
	{
		if ((*node)->data)
			free((*node)->data);
		free(*node);
		*node = NULL;
		return (NULL);
	}
	new_next = (*node)->right->right;
	if ((*node)->data)
		free((*node)->data);
	(*node)->data = (*node)->right->data;
	free((*node)->right);
	(*node)->right = new_next;
	return (*node);
}
