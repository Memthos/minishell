/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 12:53:01 by mperrine          #+#    #+#             */
/*   Updated: 2026/04/10 15:16:15 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_status	final_parsing(t_shell *shell, t_ast_lst **ast)
{
	t_status	status;

	status = SUCCESS;
	expand(ast, &status, shell, 0);
	apply_wildcards(*ast, &status);
	remove_ast_quotes(ast, &status);
	if (status == ALLOCATION_FAILURE)
	{
		perror("malloc");
		if (!shell->exitno)
			shell->exitno = 1;
		return (FAILURE);
	}
	if (!shell->exitno)
		shell->exitno = status;
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
	t_status	status;

	lxr = NULL;
	status = SUCCESS;
	if (!s)
		return (SUCCESS);
	lexer(&lxr, s, &status);
	set_final_tokens(&lxr, &status);
	checker_lxr(lxr, &status);
	complete_command_r(&lxr, shell, &status);
	lxr_lst_clear(&lxr);
	shell->exitno = status;
	if (status == ALLOCATION_FAILURE)
	{
		perror("malloc");
		shell->exitno = 1;
	}
	return (status);
}
