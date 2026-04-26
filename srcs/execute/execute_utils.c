/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 21:05:17 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/26 17:25:36 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_status	cur_cmd_init(t_ast_lst *cmd, t_shell *shell)
{
	shell->cur_cmd_index = 0;
	shell->cur_cmd = malloc(sizeof(t_string) * (ast_cmd_size(cmd) + 1));
	if (NULL == shell->cur_cmd)
	{
		perror("malloc");
		shell->exitno = FAILURE;
		return (shell->exitno);
	}
	return (SUCCESS);
}

t_status	execute_word(t_ast_lst *cmd, t_shell *shell)
{
	execute(cmd->left, shell);
	if (SUCCESS != shell->exitno)
		return (shell->exitno);
	if (NULL == shell->cur_cmd)
		if (SUCCESS != cur_cmd_init(cmd, shell))
			return (FAILURE);
	shell->cur_cmd[shell->cur_cmd_index] = cmd->data;
	++shell->cur_cmd_index;
	if (NULL == cmd->right)
	{
		shell->cur_cmd[shell->cur_cmd_index] = NULL;
		shell->exitno = execute_cmd(shell);
		free(shell->cur_cmd);
		shell->cur_cmd = NULL;
		return (shell->exitno);
	}
	execute(cmd->right, shell);
	return (shell->exitno);
}

t_status	execute_cmd_list(t_ast_lst *cmd, t_shell *shell)
{
	execute(cmd->left, shell);
	shell->oldexitno = shell->exitno;
	if (final_parsing(shell, &cmd->right))
		return (shell->exitno);
	if (AND_IF == cmd->token && SUCCESS == shell->exitno)
		execute(cmd->right, shell);
	if (OR_IF == cmd->token && SUCCESS != shell->exitno)
	{
		shell->exitno = SUCCESS;
		execute(cmd->right, shell);
	}
	return (shell->exitno);
}

t_status	execute_parentheses(t_ast_lst *cmd, t_shell *shell)
{
	pid_t		pid;
	t_status	status;

	++shell->cmp_depth;
	shell->redirects.is_cmp_redir = true;
	execute(cmd->right, shell);
	shell->redirects.is_cmp_redir = false;
	pid = fork();
	if (0 == pid)
	{
		if (-1 != shell->redirects.input_cmp_fd)
		{
			if (SUCCESS != redirect_input(&shell->redirects.input_cmp_fd))
			{
				destroy_shell(shell);
				exit(FAILURE);
			}
		}
		if (-1 != shell->redirects.output_cmp_fd)
		{
			if (0 != redirect_output(&shell->redirects.output_cmp_fd))
			{
				destroy_shell(shell);
				exit(FAILURE);
			}
		}
		ft_close(&shell->redirects.output_cmp_fd);
		ft_close(&shell->redirects.input_cmp_fd);
		execute(cmd->left, shell);
		status = shell->exitno;
		destroy_shell(shell);
		exit(status);
	}
	ft_close(&shell->redirects.output_cmp_fd);
	ft_close(&shell->redirects.input_cmp_fd);
	shell->exitno = wait_process(pid);
	--shell->cmp_depth;
	return (shell->exitno);
}
