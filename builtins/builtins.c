/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:19:17 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/10 15:17:09 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	signal = 0;

int	builtins(int ac, char **input, char **envp)
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
			if (ft_strncmp(input[i], "echo", 5) == 0)
				echo(input, envp);
			else if (ft_strncmp(input[i], "pwd", 4) == 0)
				pwd(envp);
			else if (ft_strncmp(input[i], "env", 4) == 0)
				env(&data);
			else if (ft_strncmp(input[i], "export", 7) == 0)
				export(input, data);
			i++;
		}
	}
	return (0);
}
