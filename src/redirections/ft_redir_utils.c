/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:39:40 by agiliber          #+#    #+#             */
/*   Updated: 2024/11/07 12:23:05 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	fork_redirection(t_cmd **parsing, t_env **data)
{
	int		pid;
	int		trigger;
	int		status;

	status = 0;
	trigger = 0;
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		if (exec_redirection(parsing, data, trigger))
			return (-1);
	}
	else
		waitpid(pid, &status, 0);
	(*data)->exit_code = exit_status(status, data);
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
				return (exit((*data)->exit_code), -1);
		}
		else if (tmp->redir->type == E_REDIR_OUT
			|| tmp->redir->type == E_REDIR_APP)
		{
			if (handle_redir_out(tmp, parsing, data) == -1)
				return (-1);
		}
		if (trigger == 1)
			tmp->redir_nb--;
		tmp->redir = tmp->redir->next;
		tmp->redir_nb--;
	}
	return (0);
}
