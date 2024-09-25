/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multi_piping_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:59:47 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/25 16:46:32 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		printf("fd[0] : %d\n", fd[0]);
		perror("dup2 fd[0]");
		close(fd[0]);
		return (-1);
	}
	close(fd[0]);
	close(fd[1]);
	return (0);
}

void	close_fd_multiple_cmd(t_cmd *parsing, int *old_fd)
{
	if (parsing->prev != NULL)
		close_fd(old_fd);
}

int	*transfer_fd(int *fd, int *old_fd)
{
	old_fd[0] = fd[0];
	old_fd[1] = fd[1];
	return (old_fd);
}
