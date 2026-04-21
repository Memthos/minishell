/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:06:10 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/21 14:06:30 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_status	execute_simple_cmd(t_built_in cmd, t_shell *shell)
{
	bool	redirected;

	redirected = false;
	if (-1 != shell->redirects.output_redirect_fd)
	{
		redirected = true;
		redirect_output(&shell->redirects.output_redirect_fd);
	}
	else if (-1 != shell->redirects.output_cmp_redirect_fd)
	{
		redirected = true;
		redirect_output(&shell->redirects.output_cmp_redirect_fd);
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
	if (-1 != shell->redirects.input_redirect_fd)
	{
		if (SUCCESS != redirect_input(&shell->redirects.input_redirect_fd))
		{
			destroy_shell(shell);
			exit(FAILURE);
		}
	}
	else if (-1 != shell->redirects.input_cmp_redirect_fd)
	{
		if (SUCCESS != redirect_input(&shell->redirects.input_cmp_redirect_fd))
		{
			destroy_shell(shell);
			exit(FAILURE);
		}
	}
	return (SUCCESS);
}

static t_status	execute_cmd_child_output_redirection(t_shell *shell)
{
	if (-1 != shell->redirects.output_redirect_fd)
	{
		if (SUCCESS != redirect_output(&shell->redirects.output_redirect_fd))
		{
			destroy_shell(shell);
			exit(FAILURE);
		}
	}
	else if (-1 != shell->redirects.output_cmp_redirect_fd)
	{
		if (SUCCESS != redirect_output(&shell->redirects.output_cmp_redirect_fd))
		{
			destroy_shell(shell);
			exit(FAILURE);
		}
	}
	return (SUCCESS);
}

static t_status	execute_cmd_child(t_built_in cmd, t_shell *shell)
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

t_status	execute_cmd(t_shell *shell)
{
	pid_t		pid;
	t_built_in	cmd;

	if (NULL == shell || NULL == shell->cur_cmd || 0 == shell->cur_cmd_index)
		return (FAILURE);
	cmd = get_command(*shell->cur_cmd);
	if (&cmd_exec != cmd && 0 == stack_lst_size(shell->pipe_stack))
		return (execute_simple_cmd(cmd, shell));
	pid = fork();
	if (-1 == pid)
	{
		shell->exitno = FORK_FAILURE;
		return (FORK_FAILURE);
	}
	if (0 == pid)
		execute_cmd_child(cmd, shell);
	ft_close(&shell->redirects.input_redirect_fd);
	ft_close(&shell->redirects.output_redirect_fd);
	update_pids(shell, pid);
	return (shell->exitno);
}
