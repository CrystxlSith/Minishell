/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_file1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 14:51:41 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/11 10:35:23 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	open_dup_file1(int file_fd, int *fd)
{
	if (dup2(file_fd, STDIN_FILENO) == -1)
	{
		perror("Dup2 Cmd1 issue");
		return (-1);
	}
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		perror("Dup2 failure for STDIN");
		close(fd[0]);
		close(file_fd);
		return (-1);
	}
	return (0);
}

void	execute_cmd1(int *fd, char **av, char **envp)
{
	int	input_fd;

	input_fd = open(av[1], O_RDONLY);
	if (input_fd == -1)
	{
		perror("File opening Cmd1 failure");
		return ;
	}
	if (access(av[1], R_OK) == -1)
	{
		close(input_fd);
		perror("Access Cmd1 failure");
		return ;
	}
	if (open_dup_file1(input_fd, fd) == -1)
	{
		close(input_fd);
		return ;
	}
	close(input_fd);
	close(fd[0]);
	close(fd[1]);
	check_cmd(1, av, envp);
}
