/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:39:40 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/29 12:48:31 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	fork_redirection(t_cmd **parsing, t_env **data)
{
	int		pid;
	t_cmd	*tmp;
	int		trigger;

	trigger = 0;
	tmp = *parsing;
	pid = fork();
	if (pid == -1)
		return (perror("pid "), -1);
	if (pid == 0)
	{
		if (exec_redirection(parsing, data, trigger))
			return (-1);
	}
	else
		waitpid(pid, &g_sig_status, 0);

	return (0);
}

int	exec_redirection(t_cmd **parsing, t_env **data, int trigger)
{
	t_cmd	*tmp;

	tmp = *parsing;
	while (tmp->redir_nb > 0)
	{
		if (tmp->redir->type == E_REDIR_IN)
			trigger = 1;
		if (tmp->redir->type == E_REDIR_IN)
		{
			if (exec_redir_in(parsing, data) == -1)
				return (-1);
		}
		else if (tmp->redir->type == E_REDIR_OUT
			|| tmp->redir->type == E_REDIR_APP)
		{
			if (handle_redir_out(tmp, parsing, data) == -1)
				return (perror("handle_redir_out "), -1);
		}
		if (trigger == 1)
			tmp->redir_nb--;
		tmp->redir = tmp->redir->next;
		tmp->redir_nb--;
	}
	return (0);
}
