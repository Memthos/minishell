/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 00:46:08 by juperrin          #+#    #+#             */
/*   Updated: 2026/01/24 10:42:22 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_signal = 0;

static void	sig_intercept(int signo, siginfo_t *info, void *other)
{
	(void)info;
	(void)other;
	g_signal = signo;
	printf("signal %d received\n", g_signal);
	return ;
}

t_status	init_signals(void)
{
	struct sigaction	action;

	ft_bzero(&action, sizeof(action));
	action.sa_sigaction = &sig_intercept;
	action.sa_flags = SA_SIGINFO;
	if (SUCCESS != sigaction(SIGINT, &action, NULL))
		return (FAILURE);
	if (SUCCESS != sigaction(SIGQUIT, &action, NULL))
		return (FAILURE);
	return (SUCCESS);
}
