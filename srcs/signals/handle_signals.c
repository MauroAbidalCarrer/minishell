/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:05:54 by jmaia             #+#    #+#             */
/*   Updated: 2022/03/29 20:36:42 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_handling.h"

void	set_signal_handler(t_sig_handler sig_handler)
{
	struct sigaction	sa;
	sigset_t			set;

	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGQUIT);
	sa.sa_sigaction = sig_handler;
	sa.sa_mask = set;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &sa, 0);
	sigaction(SIGQUIT, &sa, 0);
}

void	set_signal_handler_as_parent(void)
{
	struct sigaction	sa;
	sigset_t			set;

	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGTERM);
	sa.sa_handler = SIG_IGN;
	sa.sa_mask = set;
	sigaction(SIGINT, &sa, 0);
	sigaction(SIGTERM, &sa, 0);
}

void	handle_signal(int sig, siginfo_t *info, void *ucontext)
{
	(void) info;
	(void) ucontext;
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		write(1, "\33[2K\r", 5);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_sig_as_heredoc(int sig, siginfo_t *info, void *ucontext)
{
	if (sig == SIGINT || sig == SIGQUIT || sig == SIGTERM)
		ft_exit(1);
	(void)info;
	(void)ucontext;
}
