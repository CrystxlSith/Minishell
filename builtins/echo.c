/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:34:42 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/04 11:04:54 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	echo(char **input)
{
	int		i;
	char	*to_print;
	char	*tmp;
	int		words;

	i = get_index(input) + 1;
	if (ft_strncmp(input[i], "-n", 2) != 0)
		return ;
	tmp = ft_strdup("");
	words = count_words(input);
	to_print = (char *)malloc(count_letters(input) + 1);
	if (!to_print)
	{
		free(tmp);
		return ;
	}
	while (input[++i])
	{
		to_print = ft_strjoin(tmp, input[i]);
		free(tmp);
		if (i - 1 != words)
			tmp = ft_strjoin(to_print, " ");
	}
	printf("%s", to_print);
	free(to_print);
}

int	main(int ac, char **av, char **envp)
{
	int	i;

	if (ac > 1)
	{
		i = 0;
		while (i < ac)
		{
			if (ft_strncmp(av[i], "echo", 4) == 0)
				echo(av);
			else if (ft_strncmp(av[i], "pwd", 4) == 0)
				pwd(envp);
			i++;
		}
	}
	return (0);
}
