/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:19:17 by agiliber          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/09/12 14:42:33 by agiliber         ###   ########.fr       */
=======
/*   Updated: 2024/09/12 10:46:33 by jopfeiff         ###   ########.fr       */
>>>>>>> bc0d2ac07c83489f0a2cbf348fd49b451b74adeb
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtins(char **input, char **envp)
{
	int			i;
	t_env		*data;
	t_dirent	*dir;

	if (!input)
		return (0);
	data = NULL;
	dir = NULL;
	initiate_struc(&data, envp);
	i = 1;
	if (ft_strncmp(input[i], "echo", 5) == 0)
		echo(input, envp);
	else if (ft_strncmp(input[i], "pwd", 4) == 0)
		pwd();
	else if (ft_strncmp(input[i], "env", 4) == 0)
		env(&data);
	else if (ft_strncmp(input[i], "export", 7) == 0)
		export(input[i], &data);
	else if (ft_strncmp(input[i], "cd_home", 8) == 0)
		cd(input[i], &data);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	builtins(av, envp);
}
