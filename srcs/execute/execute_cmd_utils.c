/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:25:56 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/27 15:08:06 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	execute_cmd_child_input_redirection(t_shell *shell)
{
	if (-1 != shell->redirects.input_fd)
	{
		if (SUCCESS != redirect_input(&shell->redirects.input_fd))
		{
			destroy_shell(shell);
			exit(FAILURE);
		}
	}
	return (SUCCESS);
}

t_status	execute_cmd_child_output_redirection(t_shell *shell)
{
	if (-1 != shell->redirects.output_fd)
	{
		if (SUCCESS != redirect_output(&shell->redirects.output_fd))
		{
			destroy_shell(shell);
			exit(FAILURE);
		}
	}
	return (SUCCESS);
}

t_status	execute_cmd_child(t_built_in cmd, t_shell *shell)
{
	t_status	status;

	restore_signals();
	ft_close(&shell->redirects.stdin_dup);
	ft_close(&shell->redirects.stdout_dup);
	ft_close(&shell->redirects.heredoc_fd);
	execute_cmd_child_input_redirection(shell);
	execute_cmd_child_output_redirection(shell);
	status = cmd(shell->cur_cmd, shell);
	destroy_shell(shell);
	exit(status);
}

t_status	execute_simple_cmd(t_built_in cmd, t_shell *shell)
{
	bool	redirected;

	redirected = false;
	if (-1 != shell->redirects.output_fd)
	{
		redirected = true;
		redirect_output(&shell->redirects.output_fd);
	}
	else if (-1 != shell->redirects.output_cmp_fd)
	{
		redirected = true;
		redirect_output(&shell->redirects.output_cmp_fd);
	}
	shell->exitno = cmd(shell->cur_cmd, shell);
	if (redirected && dup2(shell->redirects.stdout_dup, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		shell->exitno = FAILURE;
		return (shell->exitno);
	}
	return (shell->exitno);
}
