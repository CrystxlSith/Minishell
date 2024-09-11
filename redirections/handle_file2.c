/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_file2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 14:51:41 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/11 10:34:26 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	open_dup_file2(int *fd, int file_fd)
{
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		perror("Dup2 failure for STDIN");
		close(fd[0]);
		close(file_fd);
		return (-1);
	}
	if (dup2(file_fd, STDOUT_FILENO) == -1)
	{
		perror("Dup2 Cmd2 copy failure");
		return (-1);
	}
	return (0);
}

void	execute_cmd2(int *fd, char **av, char **envp)
{
	int	output_fd;

	output_fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (output_fd == -1)
	{
		perror("File opening Cmd2 failure");
		return ;
	}
	if (access(av[4], W_OK) == -1)
	{
		close(output_fd);
		perror("Access Cmd2 failure");
		return ;
	}
	if (open_dup_file2(fd, output_fd) == -1)
	{
		close(output_fd);
		return ;
	}
	close(output_fd);
	close(fd[0]);
	close(fd[1]);
	check_cmd(4, av, envp);
}
