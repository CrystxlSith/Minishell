/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_file1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 14:51:41 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/11 13:55:06 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
