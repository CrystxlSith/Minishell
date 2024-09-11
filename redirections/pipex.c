/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 09:50:38 by agiliber          #+#    #+#             */
/*   Updated: 2024/08/29 15:30:55 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	int	fd[2];
	int	id;
	int	id2;
	int	status;

	if (ac < 5 || check_input(av) == 1)
		return (perror("Wrong arguments"), 0);
	if (pipe(fd) == -1)
		return (perror("Pipe initiation failure"), 0);
	id = fork();
	if (id == -1)
		return (perror("Fork initiation failure"), 0);
	if (id == 0)
		execute_cmd1(fd, av, envp);
	id2 = fork();
	if (id2 == -1)
		return (perror("Fork2 initiation failure"), 0);
	if (id2 == 0)
		execute_cmd2(fd, av, envp);
	close_fd(fd);
	waitpid(id, &status, 0);
	waitpid(id2, &status, 0);
	return (0);
}
