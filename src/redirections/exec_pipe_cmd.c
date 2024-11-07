/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:32:44 by agiliber          #+#    #+#             */
/*   Updated: 2024/11/07 12:23:20 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pipe_multiple_cmd(t_cmd *parsing, t_env **data, int *fd, int *old_fd)
{
	if (parsing->hdc_count != 0)
		handle_heredoc_pipe(parsing, fd);
	else if ((parsing)->prev == NULL)
		handle_first_cmd_pipe(parsing, data, fd);
	else if ((parsing)->next != NULL)
		handle_middle_cmd_pipe(old_fd, fd);
	else
		handle_last_cmd_pipe(old_fd);
	if (parsing->hdc_count != 0 && !parsing->hdc->command)
		exit((*data)->exit_code);
	exec_cmd(&parsing, data);
	return (0);
}

int	multiple_cmd_iteration(t_cmd *tmp, t_env **data, int *fd, int *old_fd)
{
	if (pipe_multiple_cmd(tmp, data, fd, old_fd) == -1)
	{
		exit((*data)->exit_code);
	}
	exit((*data)->exit_code);
}

pid_t	fork_and_execute(t_cmd *tmp, t_env **data, int *current_fd, int *old_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (close_fd(current_fd), -1);
	if (pid == 0)
	{
		if (tmp->next != NULL)
			close(current_fd[0]);
		if (tmp->hdc_count != 0 && tmp->hdc->trigger != 2)
		{
			tmp->hdc->trigger = 3;
			if (!tmp->hdc->file_name)
				create_hdc_file(tmp);
			handle_heredoc_child(tmp, data, NULL);
			exit((*data)->exit_code);
		}
		if (multiple_cmd_iteration(tmp, data, current_fd, old_fd) == -1)
		{
			exit((*data)->exit_code);
		}
		exit((*data)->exit_code);
	}
	return (pid);
}

static void	wait_all_children(t_cmd *parsing, pid_t *pid, t_env **data)
{
	t_cmd	*tmp;
	int		status;
	int		i;
	pid_t	ret_pid;

	i = 0;
	tmp = parsing;
	while (tmp != NULL)
	{
		ret_pid = waitpid(pid[i], &status, 0);
		(*data)->exit_code = exit_status(status, data);
		if (ret_pid == -1)
		{
			free(pid);
			return ;
		}
		tmp = tmp->next;
		i++;
	}
	free(pid);
}

int	exec_multiple_cmd(t_cmd **parsing, t_env **data)
{
	t_cmd	*tmp;
	int		current_fd[2];
	int		old_fd[2];
	pid_t	*pid;
	int		i;

	i = -1;
	tmp = *parsing;
	old_fd[0] = -1;
	old_fd[1] = -1;
	pid = ft_calloc(find_nbr_cmd(parsing), sizeof(pid_t));
	if (!pid)
		return (-1);
	while ((tmp) != NULL)
	{
		if (create_pipe_if_needed((tmp), current_fd) == -1)
			return (free(pid), -1);
		pid[++i] = fork_and_execute((tmp), data, current_fd, old_fd);
		if (pid[i] == -1)
			return (free(pid), -1);
		update_parent_descriptors((tmp), current_fd, old_fd);
		(tmp) = (tmp)->next;
	}
	wait_all_children(*parsing, pid, data);
	return (0);
}
