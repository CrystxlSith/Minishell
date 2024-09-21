/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:07:33 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/21 04:21:28 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// fonction pour revenir a la base des dossiers du user
char	*cd_home(char *path, t_env **data)
{
	char	*tmp_old;
	char	*tmp_new;

	path = find_in_env("HOME=", (*data)->var);
	if (!path)
	{
		perror("Home");
		return (NULL);
	}
	tmp_old = getcwd(NULL, 0);
	if (go_to_path(path) == -1)
	{
		free(path);
		free(tmp_old);
		return (NULL);
	}
	tmp_new = getcwd(NULL, 0);
	update_env(tmp_old, tmp_new, data);
	free(tmp_old);
	free(tmp_new);
	return (path);
}

// fonction pour entrer dans le dossier suivant de son choix
char	*cd_next(char *path, t_env **data)
{
	char	*next_path;
	char	*current_path;
	char	*tmp;

	current_path = getcwd(NULL, 0);
	tmp = ft_strjoin(current_path, "/");
	next_path = ft_strjoin(tmp, path);
	free(tmp);
	if (go_to_path(next_path) == -1)
	{
		free(current_path);
		free(next_path);
		perror("Cant go to Dir");
		return (NULL);
	}
	update_env(current_path, next_path, data);
	free(current_path);
	return (next_path);
}

// fonction pour entrer dans le dossier precedant de son choix
char	*cd_prev(char *path, t_env **data)
{
	char	*prev_path;
	char	*current_path;
	// int		len;

	// len = 0;
	current_path = getcwd(NULL, 0);
	prev_path = NULL;
	if ((ft_strncmp(path, "..", 3) == 0)
		|| (ft_strcmp(find_in_env("OLDPWD=", (*data)->var), current_path) == 0))
	{
		prev_path = cd_prev_newpwd(path, current_path);
		if (!prev_path)
			return (NULL);
	}
	else if (ft_strcmp(find_in_env("OLDPWD=", (*data)->var), current_path) != 0)
	{
		prev_path = cd_prev_oldpwd(current_path, data);
		if (!prev_path)
			return (NULL);
	}
	update_env(current_path, prev_path, data);
	free(current_path);
	return (prev_path);
}

void	cd_entry_compare(char *path, char *new_path, t_env **data, DIR *dir)
{
	struct dirent	*entry;

	entry = readdir(dir);
	while (entry != NULL)
	{
		if (new_path == NULL || ft_strncmp(path, "..", 3) == 0)
		{
			move_to_dir(new_path, data);
			break ;
		}
		else if (ft_strcmp(new_path, entry->d_name) == 0)
		{
			if (ft_strncmp(path, ".", 2) == 0)
				break ;
			path = ft_strtrim(path, "./");
			move_to_dir(path, data);
			break ;
		}
		entry = readdir(dir);
	}
}

void	print_env(void)
{
	printf("GETCWD : %s\n", getcwd(NULL, 0));
}

// fonction general qui ouvre le canal de navigation des dossiers
// et gere la lecture du contenu des dossiers. Appelle ensuite "move_to_dir"
// pour changer de dossier
char	*cd(char *path, t_env **data)
{
	DIR				*dir;
	char			*new_path;

	dir = opendir(find_in_env("PWD=", (*data)->var));

	if (dir == NULL)
		return (perror("opendir"), NULL);
	new_path = format_dir_path(path);
	cd_entry_compare(path, new_path, data, dir);
	return (closedir(dir), NULL);
}
