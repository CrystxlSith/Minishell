/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:00:25 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/11 13:40:22 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_path(char **envp)
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
}

void	pwd()
{
	char	*input;

	input = getcwd(NULL, 0);
	if (!input)
		return ;
	printf("%s\n", input);
	free(input);
}
