/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 10:54:56 by juperrin          #+#    #+#             */
/*   Updated: 2026/03/30 16:36:40 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_status	execute(t_ast_lst *cmd, t_shell *shell)
{
	if (NULL == cmd)
		return (shell->exitno);
	if (WORD == cmd->token)
	{
		execute(cmd->left, shell);
		if (SUCCESS != shell->exitno)
			return (shell->exitno);
		if (NULL == shell->cur_cmd)
		{
			shell->cur_cmd_index = 0;
			shell->cur_cmd = malloc(sizeof(char *) * (ast_cmd_size(cmd) + 1));
			if (NULL == shell->cur_cmd)
			{
				perror("malloc");
				shell->exitno = FAILURE;
				return (shell->exitno);
			}
		}
		shell->cur_cmd[shell->cur_cmd_index] = cmd->data;
		++shell->cur_cmd_index;
		if (NULL == cmd->right)
		{
			shell->cur_cmd[shell->cur_cmd_index] = NULL;
			shell->exitno = run_comand(shell);
			free(shell->cur_cmd);
			shell->cur_cmd = NULL;
			return (shell->exitno);
		}
		execute(cmd->right, shell);
	}
	if (PIPE == cmd->token)
	{
		++shell->pipes.pipe_depth;
		execute(cmd->left, shell);
		execute(cmd->right, shell);
		--shell->pipes.pipe_depth;
	}
	if (GREAT == cmd->token || DGREAT == cmd->token)
	{
		ft_close(&shell->redirects.output_redirect_fd);
		shell->redirects.out_flags = O_WRONLY | O_CREAT;
		if (DGREAT == cmd->token)
			shell->redirects.out_flags |= O_APPEND;
		else
			shell->redirects.out_flags |= O_TRUNC;
		shell->redirects.output_redirect_fd = open(cmd->left->data,
				shell->redirects.out_flags, 0644);
		if (-1 == shell->redirects.output_redirect_fd)
		{
			perror("open");
			shell->exitno = FAILURE;
			return (shell->exitno);
		}
		if (shell->redirects.is_cmp_redir)
		{
			ft_close(&shell->redirects.output_cmp_redirect_fd);
			shell->redirects.output_cmp_redirect_fd = shell->redirects.output_redirect_fd;
			shell->redirects.output_redirect_fd = -1;
		}
		execute(cmd->left->left, shell);
	}
	if (LESS == cmd->token)
	{
		if (access(cmd->left->data, F_OK) < 0)
		{
			error_output(cmd->left->data, FILE_NOT_FOUND);
			shell->exitno = FAILURE;
			return (FAILURE);
		}
		else if (access(cmd->left->data, R_OK) < 0)
		{
			error_output(cmd->left->data, PERMISSION_ERROR);
			shell->exitno = FAILURE;
			return (FAILURE);
		}
		ft_close(&shell->redirects.input_redirect_fd);
		shell->redirects.in_flags = O_RDONLY;
		shell->redirects.input_redirect_fd = open(cmd->left->data,
				shell->redirects.in_flags);
		if (-1 == shell->redirects.input_redirect_fd)
		{
			perror("open");
			shell->exitno = FAILURE;
			return (shell->exitno);
		}
		if (shell->redirects.is_cmp_redir)
		{
			ft_close(&shell->redirects.input_cmp_redirect_fd);
			shell->redirects.input_cmp_redirect_fd = shell->redirects.input_redirect_fd;
			shell->redirects.input_redirect_fd = -1;
		}
		execute(cmd->left->left, shell);
	}
	if (DLESS == cmd->token)
	{
		++shell->heredoc.count;
		if (shell->heredoc.count > shell->heredoc.max)
		{
			error_output(NULL, HEREDOC_COUNT_EXCEEDED);
			shell->exitno = BAD_ARG;
			return (shell->exitno);
		}
		if (heredoc_lst_add(cmd->left, &shell->heredoc.heredocs))
		{
			error_output(NULL, ALLOCATION_FAILURE);
			shell->exitno = ALLOCATION_FAILURE;
			return (shell->exitno);
		}
		execute(cmd->left->left, shell);
	}
	if (AND_IF == cmd->token || OR_IF == cmd->token)
	{
		execute(cmd->left, shell);
		wait_for_processes(shell);
		if (SIGINT + 128 == shell->exitno)
			return (shell->exitno);
		if (AND_IF == cmd->token && SUCCESS == shell->exitno)
			execute(cmd->right, shell);
		if (OR_IF == cmd->token && SUCCESS != shell->exitno)
		{
			shell->exitno = SUCCESS;
			execute(cmd->right, shell);
		}
	}
	if (CMP_CMD == cmd->token)
	{
		++shell->cmp_depth;
		shell->redirects.is_cmp_redir = true;
		execute(cmd->right, shell);
		shell->redirects.is_cmp_redir = false;
		execute(cmd->left, shell);
		ft_close(&shell->redirects.output_cmp_redirect_fd);
		ft_close(&shell->redirects.input_cmp_redirect_fd);
		--shell->cmp_depth;
	}
	return (shell->exitno);
}
