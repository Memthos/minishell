/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:52:18 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/11 09:15:43 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_status	minishell(t_shell *shell)
{
	char	*line;
	int		status;

	if (NULL == shell)
		return (SUCCESS);
	while (true)
	{
		line = readline("$>");
		if (SUCCESS != parser(line, shell))
		{
			ast_lst_clear(&shell->cmd_ast);
			error_output("Error append while parsing the command\n");
			continue ;
		}
		printf("execute returned : %d\n\n", execute(shell->cmd_ast, shell));
		printf("Now waiting for all asynchronous process to finish\n");
		shell->pids_index = 0;
		while (shell->pids_index < shell->pids_count)
		{
			waitpid(shell->pids[shell->pids_index], &status, 0);
			++shell->pids_index;
		}
		free(shell->pids);
		shell->pids_index = 0;
		shell->pids = NULL;
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
	destroy(shell);
	return (SUCCESS);
}
