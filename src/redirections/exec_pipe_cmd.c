/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:50:59 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/25 10:50:47 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pipe_multiple_cmd(t_cmd *parsing, t_env **data, int *fd, int *old_fd)
{
	if (parsing->prev == NULL)
		open_dup_pipe_out(fd);
	else if (parsing->next != NULL)
	{
		open_dup_pipe_in(old_fd);
		open_dup_pipe_out(fd);
	}
	else
		open_dup_pipe_in(old_fd);
	exec_cmd(&parsing, data);
}

void	exec_multiple_cmd(t_cmd **parsing, t_env **data)
{
	t_cmd	*tmp;
	int		fd[2];
	int		old_fd[2];
	int		pid;
	int		status;

	old_fd[0] = -1;
	old_fd[1] = -1;
	tmp = *parsing;
	while (tmp != NULL)
	{
		if (tmp->next != NULL)
		{
			if (pipe(fd) == -1)
				return ;
		}
		pid = fork();
		if (pid == -1)
			return ;
		if (pid == 0)
			pipe_multiple_cmd(tmp, data, fd, old_fd);
		else
		{
			waitpid(pid, &status, 0);
			if (old_fd[0] != -1)
				close_fd(old_fd);
			if (tmp->next != NULL)
			{
				old_fd[0] = fd[0];
				old_fd[1] = fd[1];
			}
			tmp = tmp->next;
		}
	}
	if (old_fd[0] != -1)
		close_fd(old_fd);
}
