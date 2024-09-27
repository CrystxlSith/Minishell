/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:34:42 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/27 10:34:46 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	echo(char **input, t_env **data)
{
	int		i;
	int		len;
	// char	*tmp;

	i = 2;
	len = count_words(input);
	(void)data;
	// env_var = NULL;
	while (input[i])
	{
		// if (ft_strncmp(input[i], "$", 1) == 0)
		// {
		// 	tmp = ft_strtrim(input[i], "$");
		// 	tmp = ft_strjoin(tmp, "=");
		// 	env_var = find_in_env(tmp, (*data)->var);
		// 	printf("%s", env_var);
		// 	free(tmp);
		// 	free(env_var);
		// }
		// else
		printf("%s", input[i]);
		if (i - 1 != len)
			printf("%s", " ");
		i++;
	}
}
