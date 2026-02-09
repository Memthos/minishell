/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 12:53:01 by mperrine          #+#    #+#             */
/*   Updated: 2026/02/09 16:14:30 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	checker_lxr(t_lxr_lst *lxr)
{
	//Check parenthesis
	//Add quote state to struct to be able to check invalid words
}

void	parser(char *s)
{
	t_lxr_lst	*lxr;
	t_ast_lst	*ast;
	int			ret;

	lxr = NULL;
	ret = 0;
	lexer(&lxr, s, &ret);
	free(s);
	if (ret || checker_lxr(lxr))
	{
		lxr_lst_clear(&lxr);
		exit(1);
	}
	ast = complete_command_r(&lxr);
}
