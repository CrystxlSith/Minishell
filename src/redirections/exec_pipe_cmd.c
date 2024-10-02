/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:50:59 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/02 15:56:57 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pipe_multiple_cmd(t_cmd *parsing, t_env **data, int *fd, int *old_fd)
{
	if ((parsing)->prev == NULL)
	{
		printf("%s\n", "first dup2");
		open_dup_pipe_out(fd);
	}
	else if ((parsing)->next != NULL)
	{
		printf("%s\n", "second dup2");
		open_dup_pipe_in(old_fd);
		open_dup_pipe_out(fd);
	}
	else
	{
		printf("%s\n", "third dup2");
		open_dup_pipe_in(old_fd);
	}
	exec_cmd(&parsing, data);
}

void	exec_multiple_cmd(t_cmd **parsing, t_env **data)
{
	t_cmd	*tmp;
	int		current_fd[2];
	int		old_fd[2];
	int		pid;
	int		status;

	tmp = *parsing;
	old_fd[0] = -1;
	old_fd[1] = -1;
	while (tmp != NULL)
	{
		if (tmp->next != NULL)
		{
			if (pipe(current_fd) == -1)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			printf("%s\n", "Exec pipe");
			pipe_multiple_cmd(tmp, data, current_fd, old_fd);
			close_fd(old_fd);
			exit(EXIT_SUCCESS);
		}
		else
		{
			waitpid(pid, &status, 0);
			if (tmp->next != NULL)
			{
				old_fd[0] = current_fd[0];
				old_fd[1] = current_fd[1];
				close(current_fd[1]);
			}
			tmp = tmp->next;
		}
	}
	close_fd(old_fd);
}
