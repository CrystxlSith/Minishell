/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 15:14:57 by agiliber          #+#    #+#             */
/*   Updated: 2024/11/05 17:29:16 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**get_filepath_norm(char **envp)
{
	char	*path;
	char	**full_path;

	path = find_in_env("PATH=", envp);
	if (!path)
		return (NULL);
	full_path = ft_split(path, ':');
	if (!full_path)
		return (free(path), NULL);
	free(path);
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
		if (access(full_path_cmd, X_OK) == 0)
			return (free_remaining_tab(full_path, index + 1), \
				final_path = full_path_cmd, final_path);
		free(full_path_cmd);
	}
	free(full_path);
	return (NULL);
}

int	execve_cmd(char **cmd, char **envp)
{
	char	*path;

	if (access(cmd[0], X_OK) == 0)
	{
		if (execve(cmd[0], cmd, envp) == -1)
			exit(g_sig_status);
	}
	else
	{
		path = get_filepath(cmd, envp);
		if (!path)
			return (0);
		if (execve(path, cmd, envp) == -1)
		{
			free(path);
			exit(g_sig_status);
		}
		free(path);
		free_all(cmd);
	}
	return (0);
}

int	check_cmd_minishell(t_cmd **parsing, char **envp)
{
	if ((*parsing)->hdc_count != 0)
	{
		if (execve_cmd((*parsing)->hdc->command, envp) == -1)
			return (-1);
	}
	else
	{
		if (execve_cmd((*parsing)->str, envp) == -1)
			return (-1);
	}
	return (0);
}
