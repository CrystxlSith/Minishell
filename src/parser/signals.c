/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycry <crycry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:27:40 by kali              #+#    #+#             */
/*   Updated: 2024/10/09 23:20:57 by crycry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_handler(int signum)
{
	ft_putchar_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_sig_status = 130;
	(void)signum;
}

void	here_doc_signal_handler(int signum)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	exit(EXIT_FAILURE);
	(void)signum;
}

void	init_signals(bool is_heredoc)
{
	if (is_heredoc)
		signal(SIGINT, here_doc_signal_handler);
	else
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, SIG_IGN);
	}
}
