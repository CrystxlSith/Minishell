/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:28:11 by agiliber          #+#    #+#             */
/*   Updated: 2024/11/07 12:20:41 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sigquit_handler(int signum)
{
	write(2, "quit (core dumped)\n", 19);
	(void)signum;
}

void	verify_code(t_env **data, t_replace_params *params)
{
	(void)params;
	if (g_sig_status == 2)
	{
		g_sig_status = 0;
		(*data)->exit_code = 130;
	}
}

void	parse_open(t_cmd *cmd_parsing)
{
	cmd_parsing->hdc = cmd_parsing->hdc->next;
	cmd_parsing->hdc->hdc_fd = open(cmd_parsing->hdc->prev->file_name, \
	O_CREAT | O_RDWR | O_APPEND, 0777);
}
