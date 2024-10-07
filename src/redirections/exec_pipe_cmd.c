/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:50:59 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/07 16:42:11 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pipe_multiple_cmd(t_cmd *parsing, t_env **data, int *fd, int *old_fd)
{
	if (parsing->hdc->input_nbr != 0)
	{
		if (open_dup_input(parsing->hdc->input_nbr) == -1)
			return (perror("pipe in"), -1);
	}
	else if ((parsing)->prev == NULL)
	{
		if (open_dup_pipe_out(fd) == -1)
			return (perror("pipe out"), -1);
	}
	else if ((parsing)->next != NULL)
	{
		if (open_dup_pipe_in(old_fd) == -1)
			return (perror("pipe in"), -1);
		if (open_dup_pipe_out(fd) == -1)
			return (perror("pipe out"), -1);
	}
	else
	{
		if (open_dup_pipe_in(old_fd) == -1)
			return (perror("pipe in"), -1);
	}
	exec_cmd(&parsing, data);
	return (0);
}

int	exec_multiple_cmd(t_cmd **parsing, t_env **data)
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
				return (perror("multi pipe"), -1);
		}
		pid = fork();
		if (pid == -1)
			return (perror("multi fork"), -1);
		if (pid == 0)
		{
			if (pipe_multiple_cmd(tmp, data, current_fd, old_fd) == -1)
				return (perror("multi exec"), -1);
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
	return (close_fd(old_fd), 0);
}
