/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 10:54:56 by juperrin          #+#    #+#             */
/*   Updated: 2026/03/13 14:00:31 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_status	execute(t_ast_lst *cmd, t_shell *shell)
{
	if (NULL == cmd)
		return (SUCCESS);
	if (WORD == cmd->token)
	{
		if (NULL == shell->cur_cmd)
		{
			shell->cur_cmd_index = 0;
			shell->cur_cmd = malloc(sizeof(char *) * (ast_cmd_size(cmd) + 1));
			if (NULL == shell->cur_cmd)
			{
				perror("malloc");
				shell->exitno = ALLOCATION_FAILURE;
				return (ALLOCATION_FAILURE);
			}
		}
		shell->cur_cmd[shell->cur_cmd_index] = cmd->data;
		++shell->cur_cmd_index;
		if (NULL == cmd->right)
		{
			shell->cur_cmd[shell->cur_cmd_index] = NULL;
			shell->exitno = run_comand(shell);
			return (shell->exitno);
		}
		execute(cmd->right, shell);
	}
	if (PIPE == cmd->token)
	{
		++shell->pipes.pipe_depth;
		if (!ast_pipe_count(cmd->left))
		{
			if (-1 == pipe(shell->pipes.pipe1))
			{
				perror("pipe");
				shell->exitno = PIPE_FAILURE;
				return (shell->exitno);
			}
			shell->pipes.redirect_output = true;
		}
		execute(cmd->left, shell);
		shell->pipes.redirect_output = false;
		++shell->pipes.pipe_index;
		if (shell->pipes.pipe_depth > 1)
		{
			if (0 == shell->pipes.pipe_index % 2)
			{
				if (-1 == pipe(shell->pipes.pipe1))
				{
					perror("pipe");
					shell->exitno = PIPE_FAILURE;
					return (shell->exitno);
				}
			}
			else
			{
				if (-1 == pipe(shell->pipes.pipe2))
				{
					perror("pipe");
					shell->exitno = PIPE_FAILURE;
					return (shell->exitno);
				}
			}
			shell->pipes.redirect_output = true;
		}
		shell->pipes.redirect_input = true;
		execute(cmd->right, shell);
		shell->pipes.redirect_input = false;
		if (0 == (shell->pipes.pipe_index - 1) % 2)
		{
			ft_close(&shell->pipes.pipe1[0]);
			ft_close(&shell->pipes.pipe1[1]);
		}
		else
		{
			ft_close(&shell->pipes.pipe2[0]);
			ft_close(&shell->pipes.pipe2[1]);
		}
		--shell->pipes.pipe_depth;
	}
	if (AND_IF == cmd->token || OR_IF == cmd->token)
	{
		execute(cmd->left, shell);
		wait_for_processes(shell);
		if (AND_IF == cmd->token && SUCCESS == shell->exitno)
			execute(cmd->right, shell);
		if (OR_IF == cmd->token && SUCCESS != shell->exitno)
			execute(cmd->right, shell);
	}
	if (CMP_CMD == cmd->token)
		execute(cmd->left, shell);
	return (shell->exitno);
}
