/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:00:25 by agiliber          #+#    #+#             */
/*   Updated: 2024/11/05 13:59:06 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* char	*get_path(char **envp)
{
	int		index;
	char	*path;
	char	*trim_path;

	index = 1;
	path = ft_strdup(envp[index]);
	if (!path)
		return (NULL);
	trim_path = ft_strtrim(path, "PWD=");
	if (!trim_path)
		return (free(path), NULL);
	free(path);
	return (trim_path);
} */

int	pwd(t_cmd **parsing, t_env **data)
{
	int	i;

	i = 0;
	while ((*parsing)->str[i])
		i++;
	if ((*data)->pwd)
	{
		if (i > 1 && (*parsing)->str[1][0] == '-')
		{
			ft_printf_fd(2, "bash: pwd: %c%c: invalid option\n", \
				(*parsing)->str[1][0], (*parsing)->str[1][1]);
			ft_printf_fd(2, "pwd: usage: pwd [-LP]\n");
			return (1);
		}
		else
			printf("%s\n", (*data)->pwd);
		return (0);
	}
	else
		return (1);
}
