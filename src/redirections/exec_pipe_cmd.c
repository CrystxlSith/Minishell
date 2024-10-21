/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:50:59 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/21 10:51:27 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pipe_multiple_cmd(t_cmd *parsing, t_env **data, int *fd, int *old_fd)
{
	if (parsing->hdc_count != 0)
	{
		if (pipe_heredoc(parsing, fd) == -1)
			return (perror("pipe heredoc"), -1);
	}
	else if ((parsing)->prev == NULL)
	{
		if ((parsing)->next->str == NULL
			&& ((parsing)->next->redir->type == E_REDIR_OUT
			|| (parsing)->next->redir->type == E_REDIR_APP))
		{
			parsing = (parsing)->next;
			if (exec_redirection(&parsing, data, 0) == -1)
				return (perror("pipe first cmd"), -1);
			exit(EXIT_SUCCESS);
		}
		else
		{
			if (open_dup_pipe_out(fd) == -1)
			return (perror("pipe first cmd"), -1);
		}
	}
	else if ((parsing)->next != NULL)
	{
		if (open_dup_pipe_middle(old_fd, fd) == -1)
			return (perror("pipe middle cmd"), -1);
	}
	else
	{
		if (open_dup_pipe_in(old_fd) == -1)
			return (perror("pipe final cmd"), -1);
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
		close_fd(current_fd);
		return (-1);
	}
	if (pid == 0)
	{
		if (tmp->next != NULL)
			close(current_fd[0]);
		if (multiple_cmd_iteration(tmp, data, current_fd, old_fd) == -1)
		{
			perror("multiple_cmd_iteration");
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
	return (pid);
}

int	wait_all_children(t_cmd *parsing, pid_t *pid)
{
	t_cmd	*tmp;
	int		i;
	int		status;
	pid_t	ret_pid;

	i = 0;
	tmp = parsing;
	while (tmp != NULL)
	{
		ret_pid = waitpid(pid[i], &status, 0);
		if (ret_pid == -1)
		{
			perror("waitpid failed");
			free(pid);
			return (-1);
		}
		tmp = tmp->next;
		i++;
	}
	free(pid);
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
	if (!pid)
		return (perror("ft_calloc pid failed"), -1);
	while (tmp != NULL)
	{
		if (create_pipe_if_needed(tmp, current_fd) == -1)
			return (free(pid), -1);
		pid[i] = fork_and_execute(tmp, data, current_fd, old_fd);
		if (pid[i] == -1)
			return (free(pid), -1);
		update_parent_descriptors(tmp, current_fd, old_fd);
		tmp = tmp->next;
		i++;
	}
	return (wait_all_children(*parsing, pid), 0);
}
