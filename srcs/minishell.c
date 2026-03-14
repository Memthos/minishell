/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:52:18 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/14 18:24:15 by mperrine         ###   ########.fr       */
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
			continue ;
		execute(shell->cmd_ast, shell);
		printf("execution returned : %d\n", shell->exitno);
		ast_lst_clear(&shell->cmd_ast);
		wait_for_processes(shell);
		shell->pipes.pipe_index = 0;
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
