/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:52:18 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/31 10:17:30 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_status	minishell(t_shell *shell)
{
	char		*line;
	t_status	code;
	t_cmd_lst	*cur_ast;

	while (true)
	{
		line = readline("$>");
		if (NULL == line)
			break ;
		add_history(line);
		init_execution_signals();
		if (SUCCESS != parser(line, shell))
		{
			cmds_lst_clear(&shell->cmd_ast);
			shell->exitno = 2;
			continue ;
		}
		cur_ast = shell->cmd_ast;
		while (cur_ast)
		{
			code = execute(cur_ast->ast, shell);
			wait_for_processes(shell);
			if (code && !shell->exitno)
				shell->exitno = code;
			dprintf(2, "$? : %d\n", shell->exitno);
			shell->pipes.pipe_index = 0;
			shell->exitno = SUCCESS;
			cur_ast = cur_ast->next;
		}
		cmds_lst_clear(&shell->cmd_ast);
		init_normal_signals();
	}
	return (SUCCESS);
}

int	main(int argc, char **argv, char **envp)
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
