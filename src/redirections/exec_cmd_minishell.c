/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:47:29 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/02 11:33:13 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_fork(t_cmd **parsing, t_env **data)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		exec_cmd_minishell(parsing, data);
	waitpid(pid, &status, 0);
}

void	exec_cmd_minishell(t_cmd **parsing, t_env **data)
{
	if ((*parsing)->next == NULL)
	{
		exec_cmd(parsing, data);
	}
	else
		exec_multiple_cmd(parsing, data);
}

void	exec_cmd(t_cmd **parsing, t_env **data)
{
	if ((*parsing)->redir_nb > 0)
	{
		exec_redirection(parsing, data);
	}
	else
	{
		exec_single_cmd(parsing, data);
	}
}

void	exec_single_cmd(t_cmd **parsing, t_env **data)
{
	if (check_if_builtins((*parsing)->str[0]))
		builtins((*parsing)->str, data);
	else
	{
		check_cmd_minishell(parsing, (*data)->var);
	}
}
