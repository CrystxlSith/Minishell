/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:50:59 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/08 11:07:38 by agiliber         ###   ########.fr       */
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

int	multiple_cmd_iteration(t_cmd *tmp, t_env **data, int *fd, int *old_fd)
{
	if (pipe_multiple_cmd(tmp, data, fd, old_fd) == -1)
		return (perror("multi exec"), -1);
	close_fd(old_fd);
	exit(EXIT_SUCCESS);
}

int	fork_and_execute(t_cmd *tmp, t_env **data, int *current_fd, int *old_fd)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("multi fork");
		return (-1);
	}
	if (pid == 0)
	{
		if (multiple_cmd_iteration(tmp, data, current_fd, old_fd) == -1)
		{
			perror("multiple_cmd_iteration");
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
	return (pid);
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
		if (create_pipe_if_needed(tmp, current_fd) == -1)
			return (-1);
		pid = fork_and_execute(tmp, data, current_fd, old_fd);
		if (pid == -1)
			return (-1);
		waitpid(pid, &status, 0);
		update_parent_descriptors(tmp, current_fd, old_fd);
		tmp = tmp->next;
	}
	close_fd(old_fd);
	return (0);
}
