/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:46:47 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/29 07:57:50 by jopfeiff         ###   ########.fr       */
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
	(*parsing)->hdc->next = NULL;
}

t_heredoc	*new_hdc_struc(t_cmd **parsing)
{
	t_heredoc	*new_hdc;

	(void)parsing;
	new_hdc = malloc(sizeof(t_heredoc));
	if (!new_hdc)
		return (NULL);
	new_hdc->break_word = NULL;
	new_hdc->file_name = NULL;
	new_hdc->command = NULL;
	new_hdc->trigger = 0;
	new_hdc->next = NULL;
	return (new_hdc);
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
