/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_piping_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 15:14:57 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/23 14:00:17 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	open_dup_output(int fd_in)
{
	if (dup2(fd_in, STDOUT_FILENO) == -1)
	{
		perror("dup2 fd_ouput");
		close(fd_in);
		return (-1);
	}
	close(fd_in);
	return (0);
}

int	open_dup_input(int fd_in)
{
	if (dup2(fd_in, STDIN_FILENO) == -1)
	{
		perror("dup2 fd_input");
		close(fd_in);
		return (-1);
	}
	close(fd_in);
	return (0);
}

void	close_fd(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

int	find_index_file(t_cmd *parsing, int i)
{
	while (parsing->str[i])
	{
		if (ft_strncmp(parsing->str[i], "<", 2) == 0
			|| ft_strncmp(parsing->str[i], ">", 2) == 0)
			return (i + 1);
		i++;
	}
	return (-1);
}

int	check_if_builtins(char *input)
{
	if (ft_strncmp(input, "echo", 4) == 0
		|| ft_strncmp(input, "pwd", 3) == 0
		|| ft_strncmp(input, "env", 3) == 0
		|| ft_strncmp(input, "export", 6) == 0
		|| ft_strncmp(input, "cd", 2) == 0
		|| ft_strncmp(input, "unset", 5) == 0)
		return (TRUE);
	return (FALSE);
}
