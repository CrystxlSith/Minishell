/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycry <crycry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:00:25 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/30 18:37:06 by crycry           ###   ########.fr       */
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

void	pwd(t_env **data)
{
	if ((*data)->pwd)
	{
		printf("%s\n", (*data)->pwd);
		g_sig_status = 0;
	}
	else
		g_sig_status = 1;
}
