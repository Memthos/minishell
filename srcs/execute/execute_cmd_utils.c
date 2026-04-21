/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:25:56 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/21 15:52:47 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_status	execute_cmd_child_pipe(t_shell *shell)
{
	t_pipe	*input_pipe;
	t_pipe	*output_pipe;

	input_pipe = pipe_get(shell, RIGHT);
	output_pipe = pipe_get(shell, LEFT);
	if (input_pipe && shell->redirect_input)
	{
		if (SUCCESS != redirect_input(&input_pipe->pipe[0]))
		{
			destroy_shell(shell);
			exit(FAILURE);
		}
	}
	if (output_pipe && shell->redirect_output)
	{
		if (SUCCESS != redirect_output(&output_pipe->pipe[1]))
		{
			destroy_shell(shell);
			exit(FAILURE);
		}
	}
	stack_lst_clear(&shell->pipe_stack, (void (*)(void *)) & pipe_close);
	return (SUCCESS);
}

static t_status	execute_cmd_child_input_redirection(t_shell *shell)
{
	if (-1 != shell->redirects.input_fd)
	{
		if (SUCCESS != redirect_input(&shell->redirects.input_fd))
		{
			destroy_shell(shell);
			exit(FAILURE);
		}
	}
	else if (-1 != shell->redirects.input_cmp_fd)
	{
		if (SUCCESS != redirect_input(&shell->redirects.input_cmp_fd))
		{
			destroy_shell(shell);
			exit(FAILURE);
		}
	}
	return (SUCCESS);
}

static t_status	execute_cmd_child_output_redirection(t_shell *shell)
{
	if (-1 != shell->redirects.output_fd)
	{
		if (SUCCESS != redirect_output(&shell->redirects.output_fd))
		{
			destroy_shell(shell);
			exit(FAILURE);
		}
	}
	else if (-1 != shell->redirects.output_cmp_fd)
	{
		if (0 != redirect_output(&shell->redirects.output_cmp_fd))
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
	execute_cmd_child_pipe(shell);
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
