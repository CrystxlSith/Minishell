/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multi_piping_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariannedubuard <mariannedubuard@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:59:47 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/26 15:08:12 by mariannedub      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	open_dup_pipe_out(int *fd)
{
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		printf("%s\n", "Dup2 fd1 problem");
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
	printf("%s\n", "Dup2 fd0 done");
	close(fd[0]);
	close(fd[1]);
	return (0);
}

int	open_dup_pipe_terminal(int *fd)
{
	if (dup2(STDOUT_FILENO, fd[1]) == -1)
	{
		printf("%s\n", "Dup2 fd1 problem");
		perror("dup2 fd[1]");
		close(fd[1]);
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
