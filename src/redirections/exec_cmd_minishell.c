/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:47:29 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/25 16:40:53 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_fork(t_cmd **parsing, t_env **data)
{
	int	fd[2];
	int	pid;
	int	status;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	printf("Pipe created fork : fd[0]=%d, fd[1]=%d\n", fd[0], fd[1]);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	printf("Forked process: pid=%d\n", pid);
	if (pid == 0)
	{
		if ((*parsing)->next != NULL)
		{
			printf("About to dup2 fd[1] fork: fd[0]=%d, fd[1]=%d\n", fd[0], fd[1]);
			open_dup_pipe_out(fd);
		}
		printf("%s\n", "PID OUT");
		exec_cmd_minishell(parsing, data);
		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(pid, &status, 0);
		if ((*parsing)->next != NULL)
		{
			printf("About to dup2 fd[0] fork: fd[0]=%d, fd[1]=%d\n", fd[0], fd[1]);
			open_dup_pipe_in(fd);
		}
	}
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
