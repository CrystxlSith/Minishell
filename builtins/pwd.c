/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:00:25 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/04 14:10:15 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_filepath(char **envp)
{
	int		index;
	char	*path;
	char	*trim_path;

	index = find_line(envp, "PWD");
	if (index == -1)
		return (NULL);
	path = ft_strdup(envp[index]);
	if (!path)
		return (NULL);
	trim_path = ft_strtrim(path, "PWD=");
	if (!trim_path)
		return (free(path), NULL);
	free(path);
	return (trim_path);
}

void	pwd(char **envp)
{
	char	*input;

	input = get_filepath(envp);
	if (!input)
		return ;
	printf("%s\n", input);
	free(input);
}
