/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirection_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 20:58:46 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/27 15:18:46 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_status	open_redirection(int *fd, t_string name, t_uint flags)
{
	*fd = open(name, flags, 0644);
	if (-1 == *fd)
	{
		error_output(name, strerror(errno), NO_ERR_MSG);
		return (FAILURE);
	}
	return (SUCCESS);
}

t_status	execute_out_redirection(t_ast_lst *cmd, t_shell *shell)
{
	ft_close(&shell->redirects.output_fd);
	if (shell->redirects.is_cmp_redir)
		ft_close(&shell->redirects.output_cmp_fd);
	if (cmd->left->token == AMB_RED)
	{
		amb_red_error_print(cmd->left->data);
		shell->exitno = FAILURE;
		return (shell->exitno);
	}
	if (open_redirection(&shell->redirects.output_fd, cmd->left->data,
			O_WRONLY | O_CREAT
			| O_APPEND * (DGREAT == cmd->token)
			| O_TRUNC * (DGREAT != cmd->token)))
	{
		shell->exitno = FAILURE;
		return (shell->exitno);
	}
	if (shell->redirects.is_cmp_redir)
	{
		shell->redirects.output_cmp_fd = shell->redirects.output_fd;
		shell->redirects.output_fd = -1;
	}
	execute(cmd->left->left, shell);
	return (shell->exitno);
}

static t_status	check_input_access(t_ast_lst *cmd, t_shell *shell)
{
	if (access(cmd->left->data, F_OK) < 0)
	{
		error_output(NULL, cmd->left->data, FILE_NOT_FOUND);
		shell->exitno = FAILURE;
		return (shell->exitno);
	}
	else if (access(cmd->left->data, R_OK) < 0)
	{
		error_output(NULL, cmd->left->data, PERMISSION_ERROR);
		shell->exitno = 126;
		return (shell->exitno);
	}
	return (SUCCESS);
}

t_status	execute_in_redirection(t_ast_lst *cmd, t_shell *shell)
{
	ft_close(&shell->redirects.input_fd);
	if (shell->redirects.is_cmp_redir)
		ft_close(&shell->redirects.input_cmp_fd);
	if (cmd->left->token == AMB_RED)
	{
		amb_red_error_print(cmd->left->data);
		shell->exitno = FAILURE;
		return (shell->exitno);
	}
	if (SUCCESS != check_input_access(cmd, shell))
		return (shell->exitno);
	if (open_redirection(&shell->redirects.input_fd, cmd->left->data, O_RDONLY))
	{
		shell->exitno = FAILURE;
		return (shell->exitno);
	}
	if (shell->redirects.is_cmp_redir)
	{
		shell->redirects.input_cmp_fd = shell->redirects.input_fd;
		shell->redirects.input_fd = -1;
	}
	execute(cmd->left->left, shell);
	return (shell->exitno);
}

t_status	execute_heredoc(t_ast_lst *cmd, t_shell *shell)
{
	if (shell->redirects.heredoc_fd != -1)
	{
		if (shell->redirects.is_cmp_redir)
		{
			ft_close(&shell->redirects.input_cmp_fd);
			shell->redirects.input_cmp_fd = shell->redirects.heredoc_fd;
		}
		else
		{
			ft_close(&shell->redirects.input_fd);
			shell->redirects.input_fd = shell->redirects.heredoc_fd;
		}
		shell->redirects.heredoc_fd = -1;
	}
	execute(cmd->left->left, shell);
	return (shell->exitno);
}
