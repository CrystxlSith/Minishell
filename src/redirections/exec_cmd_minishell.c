/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:47:29 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/19 13:47:28 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_fork(t_cmd **parsing, t_env **data)
{
	int	fd[2];
	int	pid;
	int	status;

	if (pipe(fd) == -1)
		return ;
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		if ((*parsing)->next != NULL)
			dup2(fd[1], STDOUT_FILENO);
		exec_cmd_minishell(parsing, data);
	}
	else
	{
		if ((*parsing)->next != NULL)
			dup2(fd[0], STDIN_FILENO);
	}
	close_fd(fd);
	waitpid(pid, &status, 0);
}

void	exec_cmd_minishell(t_cmd **parsing, t_env **data)
{
	if ((*parsing)->next == NULL)
		exec_cmd(parsing, data);
	else
		exec_multiple_cmd(parsing, data);
}

void	exec_cmd(t_cmd **parsing, t_env **data)
{
	if ((*parsing)->redir_nb > 0)
		exec_redirection(parsing, data);
	else
		exec_single_cmd(parsing, data);
}

void	exec_single_cmd(t_cmd **parsing, t_env **data)
{
	if (check_if_builtins((*parsing)->str[0]))
	{
		printf("BUILTIN %s ", (*parsing)->str[0]);
		builtins((*parsing)->str, data);
	}
	else
	{
		printf("Check CMD %s ", (*parsing)->str[0]);
		check_cmd_minishell((*parsing)->redir_nb, \
			(*parsing)->str, (*data)->var);
	}
}

void	exec_multiple_cmd(t_cmd **parsing, t_env **data)
{
	t_cmd	*tmp;

	tmp = *parsing;
	while (tmp != NULL)
	{
		execute_fork(parsing, data);
		tmp = tmp->next;
	}
}
