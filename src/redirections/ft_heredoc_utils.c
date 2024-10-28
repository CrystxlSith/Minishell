/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:46:47 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/28 11:29:22 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	initiate_hdc_struc(t_cmd **parsing)
{
	(*parsing)->hdc = malloc(sizeof(t_heredoc));
	if (!(*parsing)->hdc)
		return ;
	(*parsing)->hdc->break_word = NULL;
	(*parsing)->hdc->file_name = NULL;
	(*parsing)->hdc->command = NULL;
	(*parsing)->hdc->trigger = 0;
	(*parsing)->hdc->hdc_count = 0;
	(*parsing)->hdc->next = NULL;
}

t_heredoc	*new_hdc_struc(t_cmd **parsing)
{
	(*parsing)->hdc = malloc(sizeof(t_heredoc));
	if (!(*parsing)->hdc)
		return (NULL);
	(*parsing)->hdc->break_word = NULL;
	(*parsing)->hdc->file_name = NULL;
	(*parsing)->hdc->command = NULL;
	(*parsing)->hdc->trigger = 0;
	(*parsing)->hdc->hdc_count = 0;
	(*parsing)->hdc->next = NULL;
	return ((*parsing)->hdc);
}

int	open_heredoc_file(int flags)
{
	int	fd;

	fd = open("/tmp/heredoc.txt", flags, 0777);
	if (fd == -1)
	{
		perror("open fd heredoc");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	write_to_heredoc(int fd, char *line)
{
	if (line == NULL)
		ft_putstr_fd("\n", fd);
	ft_putstr_fd(line, fd);
	ft_putstr_fd("\n", fd);
}

int	handle_readline_error(int fd)
{
	perror("readline failed");
	close(fd);
	return (-1);
}

int	exit_failure(int fd)
{
	close(fd);
	exit(EXIT_FAILURE);
	return (-1);
}
