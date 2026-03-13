/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:52:18 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/13 13:59:10 by juperrin         ###   ########.fr       */
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
		if (SUCCESS != parser(line, shell))
		{
			ast_lst_clear(&shell->cmd_ast);
			continue ;
		}
		execute(shell->cmd_ast, shell);
		printf("execution returned : %d\n", shell->exitno);
		free(shell->cur_cmd);
		shell->cur_cmd = NULL;
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
