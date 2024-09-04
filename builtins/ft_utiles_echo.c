/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utiles_echo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 09:29:32 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/04 09:32:54 by agiliber         ###   ########.fr       */
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
