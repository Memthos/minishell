/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 00:46:08 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/17 11:35:46 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

static void	sig_intercept_normal(int signo, siginfo_t *info, void *other)
{
	(void)info;
	(void)other;
	g_signal = signo;
	if (SIGINT == g_signal)
	{
		write(STDERR_FILENO, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	return ;
}

static void	sig_intercept_heredoc(int signo, siginfo_t *info, void *other)
{
	(void)info;
	(void)other;
	g_signal = signo;
	if (SIGINT == g_signal)
	{
		write(STDERR_FILENO, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		close(STDIN_FILENO);
	}
	return ;
}

t_status	init_normal_signals(void)
{
	struct sigaction	action;

	ft_bzero(&action, sizeof(action));
	action.sa_sigaction = &sig_intercept_normal;
	action.sa_flags = 0;
	if (SUCCESS != sigaction(SIGINT, &action, NULL))
	{
		perror("sigaction");
		return (FAILURE);
	}
	action.sa_handler = SIG_IGN;
	if (SUCCESS != sigaction(SIGQUIT, &action, NULL))
	{
		perror("sigaction");
		return (FAILURE);
	}
	return (SUCCESS);
}

t_status	heredoc_signals(void)
{
	struct sigaction	action;

	ft_bzero(&action, sizeof(action));
	action.sa_sigaction = &sig_intercept_heredoc;
	if (SUCCESS != sigaction(SIGINT, &action, NULL))
	{
		perror("sigaction");
		return (FAILURE);
	}
	action.sa_handler = SIG_IGN;
	if (SUCCESS != sigaction(SIGQUIT, &action, NULL))
	{
		perror("sigaction");
		return (FAILURE);
	}
	return (SUCCESS);
}
