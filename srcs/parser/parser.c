/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 12:53:01 by mperrine          #+#    #+#             */
/*   Updated: 2026/04/03 18:46:56 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*make_str(char *input, size_t len)
{
	char	*s;
	size_t	i;

	s = malloc(sizeof(char) * (len + 1));
	if (!s)
		return (NULL);
	s[len] = '\0';
	i = 0;
	while (i++ < len)
		s[i - 1] = input[i - 1];
	return (s);
}

t_status	parser(char *s, t_shell *shell)
{
	t_lxr_lst	*lxr;
	t_cmd_lst	*cur;

	lxr = NULL;
	if (!s)
		return (SUCCESS);
	lexer(&lxr, s, &shell->exitno);
	set_final_tokens(&lxr, &shell->exitno);
	checker_lxr(lxr, &shell->exitno);
	complete_command_r(&lxr, shell, &shell->exitno);
	lxr_lst_clear(&lxr);
	cur = shell->cmd_ast;
	while (!shell->exitno && cur)
	{
		expand(cur->ast, &shell->exitno, shell, 0);
		apply_wildcards(cur->ast, &shell->exitno);
		remove_ast_quotes(cur->ast, &shell->exitno);
		cur = cur->next;
	}
	if (shell->exitno == ALLOCATION_FAILURE)
	{
		error_output("parser", shell->exitno);
		shell->exitno = 2;
	}
	return (shell->exitno);
}
