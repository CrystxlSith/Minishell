/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utiles_echo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 09:29:32 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/04 14:35:41 by agiliber         ###   ########.fr       */
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

int	get_index(char **str, char *chr)
{
	int		i;
	int		len;
	char	*result;

	len = ft_strlen(chr);
	result = NULL;
	i = -1;
	if (len == 1)
	{
		while (str[++i])
		{
			printf("STR %s\n", str[i]);
			if (ft_strchr(str[i], chr[0]))
				result = ft_strchr(str[i], chr[0]);
			printf("RESULT %s\n", result);
		}
	}
	else if (len > 1 || result != NULL)
	{
		i = -1;
		while (str[++i])
		{
			if (ft_strncmp(str[i], chr, len) == 0)
				return (i);
		}
	}
	return (i);
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

void	free_all(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

int	find_line(char **envp, char *chr)
{
	int	index;

	index = 0;
	while (envp[index])
	{
		if (ft_strncmp(envp[index], chr, ft_strlen(chr)) == 0)
			break ;
		index++;
	}
	return (index);
}