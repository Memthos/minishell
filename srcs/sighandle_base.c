/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandle_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 00:46:08 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/07 11:12:11 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_status	init_execution_signals(void)
{
	struct sigaction	action;

	ft_bzero(&action, sizeof(action));
	action.sa_sigaction = NULL;
	action.sa_handler = SIG_IGN;
	if (SUCCESS != sigaction(SIGINT, &action, NULL))
	{
		perror("sigaction");
		return (FAILURE);
	}
	if (SUCCESS != sigaction(SIGQUIT, &action, NULL))
	{
		perror("sigaction");
		return (FAILURE);
	}
	if (SUCCESS != sigaction(SIGPIPE, &action, NULL))
	{
		perror("sigaction");
		return (FAILURE);
	}
	return (SUCCESS);
}

t_status	restore_signals(void)
{
	struct sigaction	action;

	ft_bzero(&action, sizeof(action));
	action.sa_sigaction = NULL;
	action.sa_handler = SIG_DFL;
	if (SUCCESS != sigaction(SIGINT, &action, NULL))
	{
		perror("sigaction");
		return (FAILURE);
	}
	if (SUCCESS != sigaction(SIGQUIT, &action, NULL))
	{
		perror("sigaction");
		return (FAILURE);
	}
	return (SUCCESS);
}
