/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:50:59 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/15 17:57:38 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	open_dup_pipe_hdc(int *fd, int fd_hdc)
{
	if (dup2(fd_hdc, STDIN_FILENO) == -1)
	{
		perror("dup2 fd[0]");
		close(fd_hdc);
		return (-1);
	}
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2 fd[1]");
		close(fd[1]);
		close(fd[0]);
		return (-1);
	}
	close(fd_hdc);
	if (fd[1] != -1)
		close(fd[1]);
	return (0);
}

int	pipe_multiple_cmd(t_cmd *parsing, t_env **data, int *fd, int *old_fd)
{
	int	fd_out;

	if (parsing->hdc_count != 0)
	{
		fd_out = open("/tmp/heredoc.txt", O_RDONLY);
		if (parsing->next == NULL)
		{
			if (open_dup_input(fd_out) == -1)
				return (-1);
		}
		else
			open_dup_pipe_hdc(fd, fd_out);
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
	{
		perror("multi exec");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

pid_t	fork_and_execute(t_cmd *tmp, t_env **data, int *current_fd, int *old_fd)
{
	pid_t	pid;

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
	printf("PID %d\n", pid);
	return (pid);
}

int	find_nbr_cmd(t_cmd **parsing)
{
	t_cmd	*tmp;
	int		index;

	index = 0;
	tmp = *parsing;
	while (tmp != NULL)
	{
		index++;
		tmp = tmp->next;
	}
	return (index);
}

int	wait_all_children(t_cmd *parsing, pid_t *pid)
{
	int		count;
	int		status;
	int	i;

	i = 0;
	status = 0;
	count = find_nbr_cmd(&parsing);
	while (count > 0)
	{
		printf("count %d\n", count);
		waitpid(pid[i], &status, 0);
		count--;
		i++;
	}
	return (status);
}

int	exec_multiple_cmd(t_cmd **parsing, t_env **data)
{
	t_cmd	*tmp;
	int		current_fd[2];
	int		old_fd[2];
	pid_t	*pid;
	int		i;

	i = 0;
	tmp = *parsing;
	old_fd[0] = -1;
	old_fd[1] = -1;
	pid = ft_calloc(find_nbr_cmd(parsing), sizeof(pid_t));
	while (tmp != NULL)
	{
		if (create_pipe_if_needed(tmp, current_fd) == -1)
			return (-1);
		pid[i] = fork_and_execute(tmp, data, current_fd, old_fd);
		update_parent_descriptors(tmp, current_fd, old_fd);
		tmp = tmp->next;
		i++;
	}
	wait_all_children(*parsing, pid);
	return (0);
}
