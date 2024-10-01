/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariannedubuard <mariannedubuard@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:19:17 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/30 11:44:37 by mariannedub      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtins(char **input, t_env **data)
{
	int	i;

	printf("%s\n", "in builtins");
	if (!input)
		return (free_all((*data)->var), free_all(input), 0);
	i = 0;
	if (ft_strncmp(input[i], "echo", 5) == 0)
		echo(input, data);
	else if (ft_strncmp(input[i], "pwd", 4) == 0)
		pwd(data);
	else if (ft_strncmp(input[i], "env", 4) == 0)
		env(data);
	else if (ft_strncmp(input[i], "export", 7) == 0)
		export(input[++i], data);
	else if (ft_strncmp(input[i], "cd", 3) == 0)
	{
		printf("%s\n", "in cd");
		cd(input[++i], data);
	}
	else if (ft_strncmp(input[i], "unset", 6) == 0)
		unset(input[++i], data);
	else
	{
		free_all((*data)->var);
		free_all(input);
	}
	return (0);
}
