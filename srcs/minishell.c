/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:52:18 by mperrine          #+#    #+#             */
/*   Updated: 2026/04/28 14:27:46 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_asts(t_shell *shell)
{
	t_cmd_lst	*cur_ast;
	t_status	code;

	cur_ast = shell->cmd_ast;
	while (cur_ast)
	{
		if (final_parsing(shell, &cur_ast->ast))
		{
			shell->oldexitno = shell->exitno;
			shell->exitno = SUCCESS;
			cur_ast = cur_ast->next;
			continue ;
		}
		code = execute(cur_ast->ast, shell);
		close_redirections(shell);
		shell->exitno = wait_for_processes(&shell->pids, shell->exitno);
		if (code && !shell->exitno)
			shell->exitno = code;
		shell->oldexitno = shell->exitno;
		shell->exitno = SUCCESS;
		cur_ast = cur_ast->next;
	}
	return ;
}

static t_string	ft_readline(t_shell *shell)
{
	t_string	line;
	t_string	prompt;

	prompt = NULL;
	if (SUCCESS == get_prompt(shell, &prompt))
	{
		line = readline(prompt);
		free(prompt);
	}
	else
		line = readline("$> ");
	if (g_signal != 0)
	{
		shell->oldexitno = g_signal + 128;
		shell->exitno = SUCCESS;
		g_signal = 0;
	}
	if (NULL == line)
		return (NULL);
	if (!str_is_empty(line))
		add_history(line);
	return (line);
}

static t_status	minishell(t_shell *shell)
{
	t_string	line;

	while (true)
	{
		line = ft_readline(shell);
		if (!line)
			break ;
		init_execution_signals();
		if (SUCCESS != parser(line, shell))
		{
			cmds_lst_clear(&shell->cmd_ast);
			shell->oldexitno = shell->exitno;
			shell->exitno = SUCCESS;
			continue ;
		}
		exec_asts(shell);
		cmds_lst_clear(&shell->cmd_ast);
		init_normal_signals();
	}
	return (SUCCESS);
}

int	main(int argc, t_strings argv, t_strings envp)
{
	t_shell	*shell;
	int		code;

	(void)argc;
	(void)argv;
	shell = init(envp);
	if (NULL == shell)
		return (FAILURE);
	minishell(shell);
	code = shell->oldexitno;
	destroy_shell(shell);
	return (code);
}
