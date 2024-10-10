/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:50:59 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/10 15:17:51 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* void	exec_direct_cmd(t_cmd *parsing, t_env **data)
{
	t_cmd	*tmp;
	int		pid;
	int		status;

	tmp = parsing;
	while (tmp != NULL)
	{
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);
		if (pid == 0)
		{
			if (access(tmp->str[0], X_OK) != -1)
				execve_cmd(tmp->str, (*data)->var);
			else
				tmp = tmp->next;
		}
		waitpid(pid, &status, 0);
	}
}
 */
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
	//exec_direct_cmd(tmp, data);
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
