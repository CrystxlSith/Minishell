/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycry <crycry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:34:42 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/30 19:18:07 by crycry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	echo(char **input, t_env **data)
// {
// 	int		i;
// 	int		len;
// 	int		trigger;

// 	trigger = 0;
// 	if (input[1] == NULL)
// 		return ;
// 	if (ft_strncmp(input[1], "-n", 3) == 0)
// 		i = 2;
// 	else
// 	{
// 		trigger = 1;
// 		i = 1;
// 	}
// 	len = count_words(input);
// 	(void)data;
// 	while (input[i])
// 	{
// 		printf("%s", input[i]);
// 		if (i - 1 != len)
// 			printf("%s", " ");
// 		i++;
// 	}
// 	if (trigger == 1)
// 		printf("%c", '\n');
// }

int	echo(char **input, t_env **data)
{
	int		i;
	int		trigger;

	if (input[1] == NULL)
		return (1);
	if (ft_strncmp(input[1], "-n", 3) != 0)
		trigger = 1;
	else
		trigger = 0;
	if (trigger)
		i = 1;
	else
		i = 2;
	(void)data;
	while (input[i])
	{
		printf("%s", input[i]);
		if (input[++i])
			printf(" ");
	}
	if (trigger)
		printf("\n");
	return (0);
}
