/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:52:18 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/23 16:48:06 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_status	minishell(t_shell *shell)
{
	char		*line;
	t_status	code;

	while (true)
	{
		line = readline("$>");
		if (NULL == line)
			break ;
		add_history(line);
		init_execution_signals();
		if (SUCCESS != parser(line, shell))
		{
			ast_lst_clear(&shell->cmd_ast);
			continue ;
		}
		code = execute(shell->cmd_ast, shell);
		wait_for_processes(shell);
		if (code && !shell->exitno)
			shell->exitno = code;
		dprintf(2, "$? : %d\n", shell->exitno);
		ast_lst_clear(&shell->cmd_ast);
		shell->pipes.pipe_index = 0;
		shell->heredoc.count = 0;
		shell->exitno = SUCCESS;
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
