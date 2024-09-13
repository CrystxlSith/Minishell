/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utiles_echo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 09:29:32 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/13 10:30:21 by agiliber         ###   ########.fr       */
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
			i += 2;
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

int	get_index(t_env **data, char *chr)
{
	int		i;
	int		len;

	len = ft_strlen(chr);
	i = 0;
	while ((*data)->var[i])
	{
		if (ft_strncmp((*data)->var[i], chr, len) == 0)
			return (i);
		i++;
	}
	return (-1);
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
