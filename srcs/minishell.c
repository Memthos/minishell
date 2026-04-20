/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:52:18 by mperrine          #+#    #+#             */
/*   Updated: 2026/04/20 13:38:39 by juperrin         ###   ########.fr       */
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
		shell->exitno = wait_for_processes(&shell->pids);
		if (code && !shell->exitno)
			shell->exitno = code;
		shell->oldexitno = shell->exitno;
		shell->exitno = SUCCESS;
		cur_ast = cur_ast->next;
	}
	return ;
}

static t_status	minishell(t_shell *shell)
{
	char		*line;

	while (true)
	{
		line = readline("$> ");
		if (NULL == line)
			break ;
		if (!str_is_empty(line))
			add_history(line);
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

	(void)argc;
	(void)argv;
	shell = init(envp);
	if (NULL == shell)
		return (FAILURE);
	minishell(shell);
	destroy_shell(shell);
	return (SUCCESS);
}
