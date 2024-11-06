/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_hdc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 11:27:56 by agiliber          #+#    #+#             */
/*   Updated: 2024/11/05 17:28:23 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_dup_pipe_hdc(int *fd, int fd_hdc)
{
	if (dup2(fd_hdc, STDIN_FILENO) == -1)
	{
		close(fd_hdc);
		return (-1);
	}
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		close(fd[1]);
		close(fd[0]);
		return (-1);
	}
	close(fd_hdc);
	if (fd[1] != -1)
		close(fd[1]);
	return (0);
}

void	create_hdc_file(t_cmd *parsing)
{
	char	*file_name;
	int		fd_out;
	char	*index;

	index = ft_itoa(1);
	file_name = ft_strdup("/tmp/heredoc");
	file_name = ft_strjoin(file_name, index);
	file_name = ft_strjoin(file_name, ".txt");
	parsing->hdc->file_name = ft_strdup(file_name);
	fd_out = open(parsing->hdc->file_name, O_CREAT | O_RDWR | O_APPEND, 0777);
	if (fd_out == -1)
	{
		return ;
	}
	parsing->hdc->hdc_fd = fd_out;
	free(file_name);
	free(index);
}

int	pipe_heredoc(t_cmd *parsing, int *fd)
{
	int		fd_out;

	fd_out = open(parsing->hdc->file_name, O_RDONLY);
	if (fd_out == -1)
		return (-1);
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
