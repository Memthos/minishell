/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 16:07:34 by juperrin          #+#    #+#             */
/*   Updated: 2026/03/05 10:28:43 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	destroy(t_shell *shell)
{
	if (NULL == shell)
		return ;
	dict_clear(&shell->env);
	dict_clear(&shell->locals);
	ast_lst_clear(&shell->cmd_ast);
	close(shell->pipe_logic.stdin_fd);
	close(shell->pipe_logic.stdout_fd);
	free(shell);
	return ;
}
