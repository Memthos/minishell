/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 16:07:34 by juperrin          #+#    #+#             */
/*   Updated: 2026/03/11 11:17:43 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	destroy(t_shell *shell)
{
	if (NULL == shell)
		return ;
	if (NULL != shell->cur_cmd)
		free(shell->cur_cmd);
	if (NULL != shell->pids)
		free(shell->pids);
	dict_clear(&shell->env);
	dict_clear(&shell->locals);
	ast_lst_clear(&shell->cmd_ast);
	free(shell);
	printf("destroyed shell\n");
	return ;
}
