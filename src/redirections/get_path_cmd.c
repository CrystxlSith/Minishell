/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 15:14:57 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/18 14:59:37 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_line(char **envp)
{
	int	index;

	index = 0;
	while (envp[index])
	{
		if (ft_strncmp(envp[index], "PATH=", 5) == 0)
			break ;
		index++;
	}
	return (index);
}

char	**get_filepath_norm(char **envp)
{
	int		index;
	char	*path;
	char	*trim_path;
	char	**full_path;

	index = find_line(envp);
	if (index == -1)
		return (NULL);
	path = ft_strdup(envp[index]);
	if (!path)
		return (NULL);
	trim_path = ft_strtrim(path, "PATH=");
	if (!trim_path)
		return (free(path), NULL);
	free(path);
	full_path = ft_split(trim_path, ':');
	if (!full_path)
		return (free(trim_path), NULL);
	free(trim_path);
	return (full_path);
}

char	*get_filepath(char **cmd, char **envp)
{
	int		index;
	char	**full_path;
	char	*final_path;
	char	*tmp;
	char	*full_path_cmd;

	full_path = get_filepath_norm(envp);
	if (!full_path)
		return (NULL);
	final_path = NULL;
	full_path_cmd = NULL;
	tmp = NULL;
	index = -1;
	while (full_path[++index])
	{
		tmp = ft_strjoin(full_path[index], "/");
		full_path_cmd = ft_strjoin(tmp, cmd[0]);
		free(tmp);
		if (access(full_path_cmd, X_OK) == 0)
			return (final_path = full_path_cmd, \
				free_all(full_path), final_path);
		free(full_path_cmd);
	}
	free_all(full_path);
	return (NULL);
}

void	check_cmd_minishell(char **av, char **envp)
{
	char	*path;
	char	**cmd;
	int		i;

	i = 0;
	cmd = NULL;
	while (av[i])
	{
		if (av[i][0] == '<' || av[i][0] == '>')
			break ;
		cmd[i] = ft_strdup(av[i]);
		printf("%s ", cmd[i]);
		i++;
	}
	if (access(cmd[0], X_OK) == 0)
		execve(cmd[0], cmd, envp);
	else
	{
		path = get_filepath(cmd, envp);
		if (path)
		{
			execve(path, cmd, envp);
			free(path);
		}
	}
	perror("execve");
	free_all(cmd);
	free_all(av);
}
