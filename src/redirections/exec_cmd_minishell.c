/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:07:57 by agiliber          #+#    #+#             */
/*   Updated: 2024/11/05 17:25:47 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			g_sig_status = 130;
			return (WTERMSIG(status) + 128);
		}
		else if (WTERMSIG(status) == SIGQUIT)
		{
			g_sig_status = 131;
			return (WTERMSIG(status) + 128);
		}
		return (WTERMSIG(status));
	}
	return (-1);
}

int	execute_fork(t_cmd **parsing, t_env **data)
{
	int		pid;
	int		status;

	init_signals(2);
	if (check_if_builtins((*parsing)->str[0]) == 0 && (*parsing)->next == NULL
		&& (*parsing)->redir_nb == 0)
	{
		if (builtins(parsing, data) == -1)
			return (-1);
	}
	else
	{
		pid = fork();
		if (pid == -1)
			return (-1);
		if (pid == 0)
		{
			if (exec_cmd_minishell(parsing, data) == -1)
				exit(g_sig_status);
			exit(g_sig_status);
		}
		waitpid(pid, &status, 0);
		g_sig_status = exit_status(status);
	}
	return (0);
}

int	exec_cmd_minishell(t_cmd **parsing, t_env **data)
{
	if ((*parsing)->next == NULL)
	{
		if (exec_cmd(parsing, data) == -1)
			return (-1);
	}
	else
	{
		if (exec_multiple_cmd(parsing, data) == -1)
			return (-1);
	}
	return (0);
}

int	exec_cmd(t_cmd **parsing, t_env **data)
{
	if ((*parsing)->redir_nb > 0)
	{
		if (fork_redirection(parsing, data) == -1)
			return (-1);
	}
	else
	{
		if (exec_single_cmd(parsing, data) == -1)
			return (-1);
	}
	return (0);
}

int	exec_single_cmd(t_cmd **parsing, t_env **data)
{
	if ((*parsing)->hdc_count != 0
		&& check_if_builtins((*parsing)->hdc->command[0]) == 0)
	{
		if (builtins(parsing, data) == -1)
			return (-1);
	}
	else if (check_if_builtins((*parsing)->str[0]) == 0)
	{
		if (builtins(parsing, data) == -1)
			return (-1);
	}
	else
	{
		if (check_cmd_minishell(parsing, (*data)->var) == -1)
			return (-1);
	}
	return (0);
}
