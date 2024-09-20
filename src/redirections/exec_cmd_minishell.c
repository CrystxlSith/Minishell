/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:47:29 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/20 14:47:44 by agiliber         ###   ########.fr       */
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
	printf("%s\n", "Exec cmd minishell");
	if ((*parsing)->next == NULL)
		exec_cmd(parsing, data);
	else
		exec_multiple_cmd(parsing, data);
}

void	exec_cmd(t_cmd **parsing, t_env **data)
{
	printf("%s\n", "Exec cmd");
	printf("%d\n", (*parsing)->redir_nb);
	if ((*parsing)->redir_nb > 0)
		exec_redirection(parsing, data);
	else
		exec_single_cmd(parsing, data);
}

void	exec_single_cmd(t_cmd **parsing, t_env **data)
{
	if (check_if_builtins((*parsing)->str[0]))
	{
		builtins((*parsing)->str, data);
	}
	else
		check_cmd_minishell((*parsing)->redir_nb, \
			(*parsing)->str, (*data)->var);
}
