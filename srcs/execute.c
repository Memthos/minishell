/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 10:54:56 by juperrin          #+#    #+#             */
/*   Updated: 2026/03/18 14:45:42 by juperrin         ###   ########.fr       */
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
			free(shell->cur_cmd);
			shell->cur_cmd = NULL;
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
	if (GREAT == cmd->token || DGREAT == cmd->token)
	{
		if (NULL == cmd->left)
		{
			shell->exitno = BAD_ARG;
			return (shell->exitno);
		}
		ft_close(&shell->redirects.output_redirect_fd);
		shell->redirects.redirect_output = true;
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
			shell->exitno = OPEN_FAILURE;
			return (shell->exitno);
		}
		execute(cmd->left->left, shell);
	}
	if (LESS == cmd->token)
	{
		if (NULL == cmd->left)
		{
			shell->exitno = BAD_ARG;
			return (shell->exitno);
		}
		ft_close(&shell->redirects.input_redirect_fd);
		shell->redirects.redirect_input = true;
		shell->redirects.in_flags = O_RDONLY;
		shell->redirects.input_redirect_fd = open(cmd->left->data,
				shell->redirects.in_flags);
		if (-1 == shell->redirects.input_redirect_fd)
		{
			perror("open");
			shell->exitno = OPEN_FAILURE;
			return (shell->exitno);
		}
		execute(cmd->left->left, shell);
	}
	if (DGREAT == cmd->token)
	{
		++shell->heredoc.count;
		if (shell->heredoc.count > shell->heredoc.max)
		{
			error_output("maximum here-document count exceeded");
			shell->exitno = BAD_ARG;
			return (shell->exitno);
		}
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
	{
		++shell->cmp_depth;
		if (cmd->right && (GREAT == cmd->right->token
				|| DGREAT == cmd->right->token))
			shell->redirects.cmp_redirect++;
		execute(cmd->right, shell);
		execute(cmd->left, shell);
		if (shell->redirects.cmp_redirect)
		{
			shell->redirects.redirect_output = false;
			ft_close(&shell->redirects.output_redirect_fd);
			--shell->redirects.cmp_redirect;
		}
		--shell->cmp_depth;
	}
	return (shell->exitno);
}
