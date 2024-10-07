/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 15:14:57 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/07 16:11:13 by agiliber         ###   ########.fr       */
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
		if (access(full_path_cmd, X_OK) == 0)
			return (final_path = full_path_cmd, final_path);
	}
	free_all(full_path);
	return (NULL);
}

/* void	print_double_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("tab[%d] : %s\n", i, tab[i]);
		i++;
	}
} */

void	execve_cmd(char **cmd, char **envp)
{
	char	*path;

	if (access(cmd[0], X_OK) == 0)
	{
		if (execve(cmd[0], cmd, envp) == -1)
			exit(EXIT_FAILURE);
	}
	else
	{
		path = get_filepath(cmd, envp);
		if (path)
		{
			if (execve(path, cmd, envp) == -1)
			{
				free(path);
				exit(EXIT_FAILURE);
			}
			free(path);
		}
	}
}

void	check_cmd_minishell(t_cmd **parsing, char **envp)
{
	if ((*parsing)->here_doc != NULL)
		execve_cmd((*parsing)->hdc->command, envp);
	else
		execve_cmd((*parsing)->str, envp);
}

void	exec_exit(char **envp)
{
	char	*path;
	char	**tab;

	tab = (char **)malloc(sizeof(char *) * 2);
	if (!tab)
		return ;
	tab[0] = ft_strdup("exit");
	tab[1] = NULL;
	if (access(tab[0], X_OK) == 0)
	{
		if (execve(tab[0], tab, envp) == -1)
			exit(EXIT_FAILURE);
	}
	else
	{
		path = get_filepath(tab, envp);
		if (path)
		{
			if (execve(path, tab, envp) == -1)
				exit(EXIT_FAILURE);
			free(path);
			free(tab);
		}
	}
}
