/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:19:17 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/13 13:07:20 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtins(char **input, t_env **data)
{
	int			i;

	if (!input)
		return (0);
	i = 0;
	if (ft_strncmp(input[i], "echo", 5) == 0)
		echo(input, data);
	else if (ft_strncmp(input[i], "pwd", 4) == 0)
		pwd(data);
	else if (ft_strncmp(input[i], "env", 4) == 0)
		env(data);
	else if (ft_strncmp(input[i], "export", 7) == 0)
		export(input[++i], data);
	else if (ft_strncmp(input[i], "cd", 8) == 0)
		cd(input[++i], data);
	return (0);
}

/* int	main(int ac, char **av, char **envp)
{
	(void)ac;
	builtins(av, envp);
} */
