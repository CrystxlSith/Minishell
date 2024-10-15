/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multi_piping_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:59:47 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/15 10:55:25 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_dup_pipe_out(int *fd)
{
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2 fd[1]");
		close(fd[1]);
		return (-1);
	}
	close(fd[0]);
	close(fd[1]);
	return (0);
}

int	open_dup_pipe_in(int *fd)
{
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		perror("dup2 fd[0]");
		close(fd[0]);
		return (-1);
	}
	close(fd[0]);
	close(fd[1]);
	return (0);
}

int	create_pipe_if_needed(t_cmd *tmp, int *current_fd)
{
	if (tmp->next != NULL)
	{
		if (pipe(current_fd) == -1)
		{
			perror("multi pipe");
			return (-1);
		}
	}
	return (0);
}

void	update_parent_descriptors(t_cmd *tmp, int *current_fd, int *old_fd)
{
	if (tmp->next != NULL)
	{
		old_fd[0] = current_fd[0];
		old_fd[1] = current_fd[1];
		close(current_fd[1]);
	}
}
