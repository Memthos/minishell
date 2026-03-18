/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 00:46:08 by juperrin          #+#    #+#             */
/*   Updated: 2026/03/18 13:20:19 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_signal = 0;

static void	sig_intercept(int signo, siginfo_t *info, void *other)
{
	t_shell	*shell;

	(void)info;
	g_signal = signo;
	shell = (t_shell *)other;
	if (shell)
		shell->last_exitno = 128 + SIGINT;
	if (SIGINT == signo)
	{
		write(STDERR_FILENO, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
	if (SIGQUIT == signo)
	{
		printf("SIGQUIT\n");
		return ;
	}
	return ;
}

t_status	init_signals(t_shell *shell)
{
	struct sigaction	action;

	ft_bzero(&action, sizeof(action));
	action.sa_sigaction = &sig_intercept;
	action.sa_flags = SA_SIGINFO;
	if (SUCCESS != sigaction(SIGINT, &action, shell))
		return (FAILURE);
	if (SUCCESS != sigaction(SIGQUIT, &action, shell))
		return (FAILURE);
	return (SUCCESS);
}
