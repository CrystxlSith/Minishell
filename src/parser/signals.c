/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:27:40 by kali              #+#    #+#             */
/*   Updated: 2024/10/21 14:49:17 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	signal_handler(int signum)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_sig_status = signum;
	(void)signum;
}

void	here_doc_signal_handler(int signum)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	exit(EXIT_SUCCESS);
	(void)signum;
}

void	signal_sub_handler(int signum)
{
	static int	i;

	i = 0;
	signal(SIGINT, SIG_IGN);
	if (i >= 1)
		write(1, "\n", 1);
	i += 1;
	g_sig_status = signum;
	(void)signum;
}

void	setup_child_signals(void)
{
	signal(SIGINT, signal_sub_handler);
	signal(SIGQUIT, SIG_DFL);
}

void	init_signals(int is_heredoc)
{
	if (is_heredoc == 1)
	{
		signal(SIGINT, here_doc_signal_handler);
	}
	else
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, SIG_IGN);
	}
}
