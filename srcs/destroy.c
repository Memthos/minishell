/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 16:07:34 by juperrin          #+#    #+#             */
/*   Updated: 2026/02/24 10:50:00 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	destroy(t_shell *shell)
{
	if (NULL == shell)
		return ;
	dict_clear(&shell->env);
	ast_lst_clear(&shell->cmd_ast);
	free(shell);
	return ;
}
