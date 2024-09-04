/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainagt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:19:17 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/04 15:25:30 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **envp)
{
	int	i;

	if (ac > 1)
	{
		i = 0;
		while (i < ac)
		{
			if (ft_strncmp(av[i], "echo", 4) == 0)
				echo(av, envp);
			else if (ft_strncmp(av[i], "pwd", 4) == 0)
				pwd(envp);
			else if (ft_strncmp(av[i], "env", 4) == 0)
				env(envp);
			i++;
		}
	}
	return (0);
}
