/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:34:42 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/09 15:04:27 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*echo(char **input, char **envp)
{
	int		i;
	char	*to_print;
	char	*tmp;
	int		words;

	(void)envp;
	tmp = ft_strdup("");
	i = 3;
	if (ft_strncmp(input[i], "-n", 2) != 0)
		return (NULL);
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
	return (free(to_print), NULL);
}
