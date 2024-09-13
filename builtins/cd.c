/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:07:33 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/13 11:53:06 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// fonction pour revenir a la base des dossiers du user
void	cd_home(char *path, t_env **data)
{
	char	*tmp_old;
	char	*tmp_new;

	path = find_in_env("HOME=", (*data)->var);
	if (!path)
	{
		printf("%s\n", "No HOME configured");
		return ;
	}
	tmp_old = getcwd(NULL, 0);
	if (go_to_path(path) == -1)
	{
		free(path);
		free(tmp_old);
		return ;
	}
	tmp_new = getcwd(NULL, 0);
	update_env(tmp_old, tmp_new, data);
	free(tmp_old);
	free(tmp_new);
}

// fonction pour entrer dans le dossier suivant de son choix
void	cd_next(char *path, t_env **data)
{
	char	*next_path;
	char	*current_path;
	char	*tmp;

/* 	if (go_to_path(path) == TRUE)
	{
		printf("%s\n", "access dir");
		return ;
	} */
	current_path = getcwd(NULL, 0);
	tmp = ft_strjoin(current_path, "/");
	next_path = ft_strjoin(tmp, path);
	free(tmp);
	if (file_compliant(next_path) == FALSE)
	{
		free(next_path);
		perror("Cant access Dir");
		return ;
	}
	if (go_to_path(next_path) == -1)
	{
		free(current_path);
		free(next_path);
		perror("Cant go to Dir");
		return ;
	}
	update_env(current_path, next_path, data);
	free(current_path);
	free(next_path);
}

// fonction pour entrer dans le dossier precedant de son choix
void	cd_prev(char *path, t_env **data)
{
	char	*prev_path;
	char	*current_path;
	int		len;

	if (go_to_path(path) == TRUE)
		return ;
	len = 0;
	current_path = getcwd(NULL, 0);
	if (ft_strcmp(find_in_env("OLDPWD=", (*data)->var), current_path) != 0)
	{
		prev_path = cd_prev_oldpwd(current_path, data);
		if (!prev_path)
			return ;
	}
	else
	{
		prev_path = cd_prev_newpwd(path, current_path);
		if (!prev_path)
			return ;
	}
	update_env(current_path, prev_path, data);
	free(current_path);
	free(prev_path);
}

// fonction general qui appelle les autres fonctions
// de CD a utiliser dans builtins
void	cd(char *path, t_env **data)
{
	DIR				*dir;
	struct dirent	*entry;

	(void)data;
	dir = opendir(".");
	if (dir == NULL)
	{
		perror("opendir");
		return ;
	}
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (ft_strcmp(path, entry->d_name) == 0)
			move_to_dir(path, data);
		entry = readdir(dir);
	}
	closedir(dir);
}

void	move_to_dir(char *path, t_env **data)
{
	printf("PATH INPUT : %s\n", path);
	if (path == NULL || ft_strcmp(path, "") == 0)
	{
		printf("%s\n", "path home");
		cd_home(path, data);
		printf("PATH OUTPUT : %s\n", path);
		free(path);
	}
	else if (ft_strncmp(path, "../", 3) == 0
		|| ft_strncmp(path, "..", 2) == 0)
	{
		printf("%s\n", "path prev");
		cd_prev(path, data);
		printf("PATH OUTPUT : %s\n", path);
		free(path);
	}
	else if (path != NULL || ft_strncmp(path, "./", 2) == 0)
	{
		printf("%s\n", "path next");
		cd_next(path, data);
		printf("PATH OUTPUT : %s\n", path);
		free(path);
	}
}
