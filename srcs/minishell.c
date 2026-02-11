/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:52:18 by mperrine          #+#    #+#             */
/*   Updated: 2026/02/11 13:09:11 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	t_lxr_lst *lst = NULL;
	char *line = readline("> ");
	lexer(&lst, line);
	while (lst)
	{
		printf("::%s::TOKEN=%d::P_DPT=%ld::\n", lst->data, lst->token, lst->p_dpt);
		lst = lst->next;
	}
}

//("ARG=test" && HELLO=world) || echo $ARG | echo "$HELLO"
