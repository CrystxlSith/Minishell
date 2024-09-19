/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:50:59 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/19 16:04:55 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pipe_multiple_cmd(t_cmd *parsing, t_env **data, int *fd, int *old_fd)
{
	printf("tmp->index %d\n", parsing->index);
	if (parsing->index == 0)
		open_dup_pipe_in(fd);
	else if (parsing->next != NULL)
	{
		open_dup_pipe_out(old_fd);
		open_dup_pipe_in(fd);
	}
	else
		open_dup_pipe_out(old_fd);
	exec_cmd(&parsing, data);
	close_fd(fd);
}

void	exec_multiple_cmd(t_cmd **parsing, t_env **data)
{
	t_cmd	*tmp;
	int		fd[2];
	int		*old_fd;
	int		pid;
	int		status;

	tmp = *parsing;
	while (tmp != NULL)
	{
		if (pipe(fd) == -1)
			return ;
		pid = fork();
		if (pid == -1)
			return ;
		if (pid == 0)
			pipe_multiple_cmd(tmp, data, fd, old_fd);
		else
		{
			waitpid(pid, &status, 0);
			close_fd_multiple_cmd(tmp, old_fd);
			old_fd = transfer_fd(fd, old_fd);
			tmp = tmp->next;
		}
	}
	close_fd(old_fd);
}
