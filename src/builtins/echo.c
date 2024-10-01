/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: mariannedubuard <mariannedubuard@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:34:42 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/30 13:11:44 by mariannedub      ###   ########.fr       */
=======
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:34:42 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/27 10:34:46 by kali             ###   ########.fr       */
>>>>>>> e230fa8f0608e785cc07771d7c7705d805deaa29
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
<<<<<<< HEAD
=======
	// env_var = NULL;
>>>>>>> e230fa8f0608e785cc07771d7c7705d805deaa29
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
