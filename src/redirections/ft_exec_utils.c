/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 15:14:57 by agiliber          #+#    #+#             */
/*   Updated: 2024/11/05 17:31:26 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_dup_output(int fd_in)
{
	if (dup2(fd_in, STDOUT_FILENO) == -1)
	{
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
		close(fd_in);
		return (-1);
	}
	close(fd_in);
	return (0);
}

void	close_fd(int *fd)
{
	if (fd[0] >= 0)
		close(fd[0]);
	if (fd[1] >= 0)
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
	if (input == NULL)
		return (-1);
	if (ft_strncmp(input, "echo", 5) == 0
		|| ft_strncmp(input, "pwd", 4) == 0
		|| ft_strncmp(input, "env", 4) == 0
		|| ft_strncmp(input, "export", 7) == 0
		|| ft_strncmp(input, "cd", 3) == 0
		|| ft_strncmp(input, "exit", 5) == 0
		|| ft_strncmp(input, "unset", 6) == 0)
		return (0);
	return (-1);
}
