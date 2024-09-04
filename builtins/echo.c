/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:34:42 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/03 17:20:44 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_words(char **str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (ft_strncmp(str[i], "echo", 4) == 0)
		{
			i++;
			while (str[i])
			{
				count++;
				i++;
			}
			return (count);
		}
		i++;
	}
	return (0);
}

int	get_index(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strncmp(str[i], "echo", 4) == 0)
			return (i);
		i++;
	}
	return (0);
}

int	count_letters(char **str)
{
	int	i;
	int	count;
	int	letters;

	i = 0;
	count = count_words(str);
	letters = 0;
	while (str[i])
	{
		letters += ft_strlen(str[i]);
		i++;
	}
	letters += count - 1;
	return (letters);
}

char	*echo(char **input)
{
	int		i;
	char	*to_print;
	char	*tmp;
	int		words;

	i = get_index(input) + 1;
	if (ft_strncmp(input[i], "-n", 2) != 0)
		return (NULL);
	tmp = ft_strdup("");
	words = count_words(input);
	to_print = (char *)malloc(count_letters(input) + 1);
	if (!to_print)
		return (free(tmp), NULL);
	while (input[++i])
	{
		to_print = ft_strjoin(tmp, input[i]);
		free(tmp);
		if (i - 1 != words)
			tmp = ft_strjoin(to_print, " ");
	}
	printf("%s", to_print);
	free(to_print);
	return (NULL);
}

int	main(int ac, char **av)
{
	(void)ac;
	echo(av);
	return (0);
}
