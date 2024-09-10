/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:19:17 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/10 17:45:28 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	signal = 0;

int	main(int ac, char **input, char **envp)
{
	int			i;
	t_env		*data;
	t_dirent	*dir;

	if (ac > 1)
	{
		if (signal == 0)
		{
			data = NULL;
			dir = NULL;
			initiate_struc(&data, envp);
			initiate_dir_list(&dir);
		}
		i = 0;
		while (i < ac)
		{
			if (ft_strncmp(input[i], "echo", 5) == 0)
				echo(input, envp);
			else if (ft_strncmp(input[i], "pwd", 4) == 0)
				pwd(envp);
			else if (ft_strncmp(input[i], "env", 4) == 0)
				env(&data);
			else if (ft_strncmp(input[i], "export", 7) == 0)
				export(input, data);
			else if (ft_strncmp(input[i], "cd", 3) == 0)
				cd(ac, input, &dir, envp);
			i++;
		}
	}
	return (0);
}
