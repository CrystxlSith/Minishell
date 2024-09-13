/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:34:42 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/13 10:14:54 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* char	*get_to_print(char **input, char *tmp, char *to_print)
{
	int		i;
	int		words;
	char	*env_var;
	int		len;

	i = 2;
	words = count_words(input);
	len = 0;
	while (input[i])
	{
		if (ft_strncmp(input[i], "$", 1) == 0)
		{
			tmp = ft_strtrim(input[i], "$");
			env_var = getenv(tmp);
			printf("%s", env_var);
			free(tmp);
			free(env_var);
		}
		size = count_letters(input) + len;
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
} */

void	echo(char **input, t_env **data)
{
	int		i;
	char	*env_var;
	int		len;
	char	*tmp;

	i = 3;
	len = count_words(input);
	env_var = NULL;
	while (input[i])
	{
		if (ft_strncmp(input[i], "$", 1) == 0)
		{
			tmp = ft_strtrim(input[i], "$");
			tmp = ft_strjoin(tmp, "=");
			env_var = find_in_env(tmp, (*data)->var);
			printf("%s", env_var);
			free(tmp);
			free(env_var);
		}
		else
			printf("%s", input[i]);
		if (i - 1 != len)
			printf("%s", " ");
		i++;
	}
}
