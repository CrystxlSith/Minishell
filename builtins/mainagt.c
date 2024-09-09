/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainagt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:19:17 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/09 17:21:22 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	signal = 0;

int	main(int ac, char **av, char **envp)
{
	int		i;
	t_env	*data;

	if (ac > 1)
	{
		if (signal == 0)
		{
			data = NULL;
			initiate_struc(&data, envp);
		}
		i = 0;
		while (i < ac)
		{
			if (ft_strncmp(av[i], "echo", 5) == 0)
				echo(av, envp);
			else if (ft_strncmp(av[i], "pwd", 4) == 0)
				pwd(envp);
			else if (ft_strncmp(av[i], "env", 4) == 0)
				env(&data);
			else if (ft_strncmp(av[i], "export", 7) == 0)
				export(av, data);
			i++;
		}
	}
	return (0);
}
