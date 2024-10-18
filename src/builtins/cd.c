/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:07:33 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/11 16:46:44 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// fonction pour revenir a la base des dossiers du user
void	cd_home(char *path, t_env **data)
{
	char	*tmp_old;
	char	*tmp_new;

	path = find_in_env("HOME=", (*data)->var);
	if (!path)
	{
		perror("Home");
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
	char	*tmp2;

	current_path = getcwd(NULL, 0);
	tmp2 = ft_strdup(current_path);
	tmp = ft_strjoin(tmp2, "/");
	next_path = ft_strjoin(tmp, path);
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

	current_path = getcwd(NULL, 0);
	prev_path = NULL;
	if ((ft_strncmp(path, "..", 3) == 0)
		|| (ft_strcmp(find_in_env("OLDPWD=", (*data)->var), current_path) == 0))
	{
		printf("%s\n", "in cd prev newpwd");
		prev_path = cd_prev_newpwd(path, current_path);
		if (!prev_path)
			return ;
	}
	else if (ft_strcmp(find_in_env("OLDPWD=", (*data)->var), current_path) != 0)
	{
		prev_path = cd_prev_oldpwd(current_path, data);
		if (!prev_path)
			return ;
	}
	update_env(current_path, prev_path, data);
	free(current_path);
	free(prev_path);
}

void	cd_entry_compare(char *path, char *new_path, t_env **data, DIR *dir)
{
	struct dirent	*entry;

	entry = readdir(dir);
	printf("%s\n", "in cd entry compare");
	while (entry != NULL)
	{
		if (new_path == NULL || ft_strncmp(path, "..", 3) == 0)
		{
			printf("%s\n", "in move to dir ..");
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

// fonction general qui ouvre le canal de navigation des dossiers
// et gere la lecture du contenu des dossiers. Appelle ensuite "move_to_dir"
// pour changer de dossier
/* char	*cd(char *path, t_env **data)
{
	DIR		*dir;
	DIR		*long_dir;
	char	*new_path;

	printf("Path cd : %s\n", path);
	long_dir = opendir(path);
	if (long_dir != NULL)
	{
		printf("%s\n", "in long dir");
		new_path = find_in_env("PWD=", (*data)->var);
		chdir(path);
		path = getcwd(NULL, 0);
		update_env(new_path, path, data);
		free(path);
		closedir(long_dir);
	}
	else
	{
		printf("%s\n", "in short dir");
		printf("PWD %s\n", find_in_env("PWD=", (*data)->var));
		dir = opendir(find_in_env("PWD=", (*data)->var));
		if (dir == NULL)
			return (perror("opendir"), NULL);
		new_path = format_dir_path(path);
		printf("new_path : %s\n", new_path);
		cd_entry_compare(path, new_path, data, dir);
		free(new_path);
		printf("%s\n", "path free");
		closedir(dir);
	}
	return (NULL);
} */

char	*cd(char *path, t_env **data)
{
	DIR		*dir;
	char	*new_path;

	dir = opendir(path);
	if (dir != NULL)
	{
		new_path = getcwd(NULL, 0);
		chdir(path);
		path = getcwd(NULL, 0);
		update_env(new_path, path, data);
		free(path);
		free(new_path);
		closedir(dir);
		return (NULL);
	}
	else
	{
		perror("cd");
		return (NULL);
	}
}
