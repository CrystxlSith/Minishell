/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 15:14:57 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/16 14:10:27 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_input(char **str)
{
	int	j;

	j = 1;
	while (str[1 + j] && j < 3)
	{
		if (check_space(str[1 + j]) == 1)
			return (1);
		j++;
	}
	return (0);
}

int	check_space(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (str[i])
	{
		if (str[i] == 32)
			count = 1;
		else
			return (0);
		i++;
	}
	if (count == 1)
		return (1);
	return (0);
}

void	close_fd(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}
