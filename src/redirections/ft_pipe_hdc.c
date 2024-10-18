/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_hdc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 11:27:56 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/17 11:29:14 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_dup_pipe_hdc(int *fd, int fd_hdc)
{
	if (dup2(fd_hdc, STDIN_FILENO) == -1)
	{
		perror("dup2 fd[0]");
		close(fd_hdc);
		return (-1);
	}
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2 fd[1]");
		close(fd[1]);
		close(fd[0]);
		return (-1);
	}
	close(fd_hdc);
	if (fd[1] != -1)
		close(fd[1]);
	return (0);
}

int	pipe_heredoc(t_cmd *parsing, int *fd)
{
	int	fd_out;

	fd_out = open("/tmp/heredoc.txt", O_RDONLY);
	if (parsing->next == NULL)
	{
		if (open_dup_input(fd_out) == -1)
			return (-1);
	}
	else
	{
		if (open_dup_pipe_hdc(fd, fd_out) == -1)
			return (-1);
	}
	return (0);
}

int	find_nbr_cmd(t_cmd **parsing)
{
	t_cmd	*tmp;
	int		index;

	index = 0;
	tmp = *parsing;
	while (tmp != NULL)
	{
		index++;
		tmp = tmp->next;
	}
	return (index);
}
