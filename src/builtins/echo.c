/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:34:42 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/01 10:02:26 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	echo(char **input, t_env **data)
{
	int		i;
	int		len;
	int		trigger;

	trigger = 0;
	if (ft_strncmp(input[1], "-n", 3) == 0)
		i = 2;
	else
	{
		trigger = 1;
		i = 1;
	}
	len = count_words(input);
	(void)data;
	// env_var = NULL;
	while (input[i])
	{
		printf("%s", input[i]);
		if (i - 1 != len)
			printf("%s", " ");
		i++;
	}
	if (trigger == 1)
		printf("%c", '\n');
}
