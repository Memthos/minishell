/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:52:18 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/19 13:34:55 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_status	minishell(t_shell *shell)
{
	char	*line;

	if (NULL == shell)
		return (SUCCESS);
	while (true)
	{
		line = readline("$>");
		add_history(line);
		if (SUCCESS != parser(line, shell))
		{
			ast_lst_clear(&shell->cmd_ast);
			continue ;
		}
		shell->last_exitno = execute(shell->cmd_ast, shell);
		wait_for_processes(shell);
		if (shell->exitno)
			shell->last_exitno = shell->exitno;
		dprintf(2, "$? : %d\n", shell->last_exitno);
		ast_lst_clear(&shell->cmd_ast);
		shell->pipes.pipe_index = 0;
		shell->heredoc.count = 0;
		shell->exitno = SUCCESS;
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
