/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:27:40 by kali              #+#    #+#             */
/*   Updated: 2024/10/11 10:58:29 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	signal_handler(int signum)
{
	printf("\n");
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
	exit(EXIT_FAILURE);
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
}

void	init_signals(int is_heredoc)
{
	if (is_heredoc == 1)
		signal(SIGINT, here_doc_signal_handler);
	else
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, SIG_IGN);
	}
}
