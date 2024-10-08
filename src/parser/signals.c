/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:27:40 by kali              #+#    #+#             */
/*   Updated: 2024/10/08 08:28:07 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_handler(int signum)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_sig_status = 130;
	(void)signum;
}

void	here_doc_signal_handler(int signum)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_sig_status = 130;
	(void)signum;
}

void	init_signals(int is_heredoc)
{
	if (is_heredoc)
		signal(SIGINT, here_doc_signal_handler);
	else
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, SIG_IGN);
	}
}
