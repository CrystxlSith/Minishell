/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 15:14:57 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/24 15:16:27 by agiliber         ###   ########.fr       */
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

int	get_size_cmd(char **cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmd[i])
	{
		if (cmd[i][0] == '<')
			i++;
		i++;
		while (cmd[i][0] != '>')
		{
			i++;
			count++;
		}
	}
	return (count);
}

char	**format_cmd_outredir(char **cmd)
{
	int		i;
	int		j;
	char	**new_cmd;
	int		len;

	i = 0;
	j = 0;
	len = get_size_cmd(cmd);
	new_cmd = (char **)malloc(len + 1);
	while (cmd[i] && cmd[i][0] != '>' && j < len)
	{
		if (cmd[i][0] == '<')
			i = i + 2;
		new_cmd[j] = ft_strdup(cmd[i]);
		printf("%s\n", new_cmd[j]);
		j++;
		i++;
	}
	new_cmd[j] = NULL;
	return (new_cmd);
}

char	**format_cmd_inredir(char **cmd)
{
	int		i;
	char	**new_cmd;
	int		len;

	i = 0;
	len = get_size_cmd(cmd);
	new_cmd = (char **)malloc(len + 1);
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
	print_double_tab(new_cmd);
	return (new_cmd);
}

void	print_double_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("tab[%d] : %s\n", i, tab[i]);
		i++;
	}
}

void	check_cmd_minishell(t_cmd **parsing, char **envp)
{
	char	*path;
	char	**new_cmd;

	new_cmd = NULL;
	printf("parsing > redir %d\n", (*parsing)->redir_nb);
	if ((*parsing)->redir_nb > 0)
	{
		print_double_tab((*parsing)->str);
		if ((*parsing)->redir->type == E_REDIR_IN)
		{
			printf("%s\n", "IN DIR");
			new_cmd = format_cmd_outredir((*parsing)->str);
			print_double_tab(new_cmd);
		}
		else if ((*parsing)->redir->type == E_REDIR_OUT)
		{
			printf("%s\n", "OUT DIR");
			new_cmd = format_cmd_outredir((*parsing)->str);
			print_double_tab(new_cmd);
		}
	}
	else
	{
		new_cmd = (*parsing)->str;
		print_double_tab(new_cmd);
	}
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
}
