/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 12:53:01 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/23 12:48:45 by mperrine         ###   ########.fr       */
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
	t_status	status;

	lxr = NULL;
	status = SUCCESS;
	if (!s)
		return (SUCCESS);
	lexer(&lxr, s, &status);
	if (!status)
	{
		set_final_tokens(lxr);
		checker_lxr(lxr, &status);
	}
	if (!status)
		shell->cmd_ast = complete_command_r(&lxr, &status);
	lxr_lst_clear(&lxr);
	if (!status)
		expand(shell->cmd_ast, &status, shell->env);
	if (!status)
		apply_wildcards(shell->cmd_ast, &status);
	if (!status)
		remove_ast_quotes(shell->cmd_ast, &status);
	if (status == ALLOCATION_FAILURE || status == READDIR_FAILURE)
		error_output("parser", status);
	return (status);
}
