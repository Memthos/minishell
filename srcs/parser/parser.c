/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 12:53:01 by mperrine          #+#    #+#             */
/*   Updated: 2026/04/07 10:15:08 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_status	final_parsing(t_shell *shell, t_ast_lst **ast)
{
	expand(ast, &shell->exitno, shell, 0);
	apply_wildcards(*ast, &shell->exitno);
	remove_ast_quotes(ast, &shell->exitno);
	if (shell->exitno == ALLOCATION_FAILURE)
	{
		error_output("execution", shell->exitno);
		shell->exitno = 1;
	}
	if (shell->exitno)
		return (FAILURE);
	return (SUCCESS);
}

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

	lxr = NULL;
	if (!s)
		return (SUCCESS);
	lexer(&lxr, s, &shell->exitno);
	set_final_tokens(&lxr, &shell->exitno);
	checker_lxr(lxr, &shell->exitno);
	complete_command_r(&lxr, shell, &shell->exitno);
	lxr_lst_clear(&lxr);
	if (shell->exitno == ALLOCATION_FAILURE)
	{
		error_output("parser", shell->exitno);
		shell->exitno = 1;
	}
	return (shell->exitno);
}
