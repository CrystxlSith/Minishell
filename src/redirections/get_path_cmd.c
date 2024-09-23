/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 15:14:57 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/23 10:51:09 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char	**format_cmd_outredir(char **cmd)
{
	int		i;
	int		j;
	char	**new_cmd;

	i = 0;
	j = 0;
	new_cmd = NULL;
	while (cmd[i])
	{
		while (cmd[i][0] != '<')
			i++;
		i++;
		new_cmd[j] = ft_strdup(cmd[i + j]);
		j++;
	}
	new_cmd[j] = NULL;
	return (new_cmd);
}

char	**format_cmd_inredir(char **cmd)
{
	int		i;
	char	**new_cmd;

	i = 0;
	new_cmd = NULL;
	while (cmd[i])
	{
		if (cmd[i][0] == '>')
			break ;
		else
			new_cmd[i] = ft_strdup(cmd[i]);
		if (cmd[i][0] == '<')
			i++;
		i++;
	}
	new_cmd[i] = NULL;
	return (new_cmd);
}

void	check_cmd_minishell(t_cmd **parsing, char **cmd, char **envp)
{
	char	*path;
	char	**new_cmd;

	if ((*parsing)->redir_nb > 0)
	{
		if ((*parsing)->redir->type == E_REDIR_IN)
			new_cmd = format_cmd_inredir(cmd);
		else
			new_cmd = format_cmd_outredir(cmd);
	}
	else
		new_cmd = cmd;
	if (access(new_cmd[0], X_OK) == 0)
		execve(new_cmd[0], new_cmd, envp);
	else
	{
		path = get_filepath(new_cmd, envp);
		if (path)
		{
			execve(path, new_cmd, envp);
			free(path);
		}
	}
	free_all(new_cmd);
	free_all(cmd);
}
