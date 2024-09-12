/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:34:42 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/12 16:24:58 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_to_print(char **input, char *tmp, char *to_print)
{
	int	i;
	int	words;

	i = 2;
	words = count_words(input);
	while (input[i])
	{
		to_print = ft_strjoin(tmp, input[i]);
		if (!to_print)
			return (free(tmp), NULL);
		free(tmp);
		if (i - 1 != words)
		{
			tmp = ft_strjoin(to_print, " ");
			if (!tmp)
				return (free(to_print), NULL);
		}
		i++;
	}
	return (to_print);
}

char	*print_to_print(char **input, char *tmp, int size)
{
	char	*to_print;

	to_print = (char *)malloc(size + 1);
	if (!to_print)
		return (free(tmp), NULL);
	to_print = get_to_print(input, tmp, to_print);
	if (!to_print)
		return (free(tmp), NULL);
	return (to_print);
}

char	*echo(char **input)
{
	char	*to_print;
	char	*tmp;
	char	*env_var;
	int		len;
	int		size;

	tmp = ft_strdup("");
	env_var = NULL;
	len = 0;
	if (ft_strncmp(input[2], "$", 1) == 0)
	{
		tmp = ft_strtrim(input[2], "$");
		env_var = getenv(tmp);
		free(tmp);
	}
	if (env_var != NULL)
	{
		len = ft_strlen(env_var);
		tmp = ft_strdup(env_var);
		free(env_var);
	}
	size = count_letters(input) + len;
	to_print = print_to_print(input, tmp, size);
	return (printf("%s", to_print), free(to_print), NULL);
}
