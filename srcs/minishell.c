/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:52:18 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/16 14:52:09 by juperrin         ###   ########.fr       */
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
		printf("%d\n", shell->exitno);
		ast_lst_clear(&shell->cmd_ast);
		printf("%d\n", wait_for_processes(shell));
		shell->pipes.pipe_index = 0;
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
