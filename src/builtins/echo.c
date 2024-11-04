/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:34:42 by agiliber          #+#    #+#             */
/*   Updated: 2024/11/04 07:54:53 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_flag(char **input)
{
	int	i;
	int	j;

	i = 1;
	while (input[i])
	{
		j = 1;
		while (input[i][j])
		{
			if (input[i][0] != '-')
				return (i);
			if (input[i][j] != 'n')
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

int	echo(char **input, t_env **data)
{
	int		i;
	int		trigger;
	int		index = 0;

	if (input[1] == NULL)
		return (1);
	index = check_flag(input);
	if (index != 1)
		trigger = 1;
	else
		trigger = 0;
	if (!trigger)
		i = 1;
	else
		i = index;
	(void)data;
	while (input[i])
	{
		printf("%s", input[i]);
		if (input[++i])
			printf(" ");
	}
	if (!trigger)
		printf("\n");
	return (0);
}
