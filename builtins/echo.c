/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:34:42 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/13 10:28:41 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	echo(char **input, t_env **data)
{
	int		i;
	char	*env_var;
	int		len;
	char	*tmp;

	i = 2;
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
