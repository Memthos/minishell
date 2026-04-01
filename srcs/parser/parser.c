/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 12:53:01 by mperrine          #+#    #+#             */
/*   Updated: 2026/04/01 17:34:41 by mperrine         ###   ########.fr       */
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
	t_cmd_lst	*cur;

	lxr = NULL;
	status = SUCCESS;
	if (!s)
		return (SUCCESS);
	lexer(&lxr, s, &status);
	if (!status)
		set_final_tokens(&lxr);
	checker_lxr(lxr, &status);
	complete_command_r(&lxr, shell, &status);
	lxr_lst_clear(&lxr);
	cur = shell->cmd_ast;
	while (!status && cur)
	{
		expand(cur->ast, &status, shell);
		apply_wildcards(cur->ast, &status);
		remove_ast_quotes(cur->ast, &status);
		cur = cur->next;
	}
	if (status == ALLOCATION_FAILURE || status == READDIR_FAILURE)
		error_output("parser", status);
	return (status);
}
