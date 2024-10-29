/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:07:33 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/25 16:17:27 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// fonction pour revenir a la base des dossiers du user
int	cd_home(char *path, t_env **data)
{
	char	*tmp_old;
	char	*tmp_new;

	path = find_in_env("HOME=", (*data)->var);
	if (!path)
	{
		perror("Home");
		return (-1);
	}
	tmp_old = getcwd(NULL, 0);
	if (go_to_path(path) == -1)
	{
		free(path);
		free(tmp_old);
		return (-1);
	}
	tmp_new = getcwd(NULL, 0);
	free(path);
	update_env(tmp_old, tmp_new, data);
	free(tmp_old);
	free(tmp_new);
	return (0);
}

// fonction pour entrer dans le dossier precedant de son choix
int	cd_prev(char *path, t_env **data)
{
	char	*prev_path;
	char	*current_path;
	char	*tmp;

	current_path = getcwd(NULL, 0);
	prev_path = NULL;
	tmp = find_in_env("OLDPWD=", (*data)->var);
	if ((ft_strncmp(path, "..", 3) == 0) || (ft_strcmp(tmp, current_path) == 0))
	{
		prev_path = cd_prev_newpwd(path, current_path);
		if (!prev_path)
			return (free(tmp), -1);
	}
	else if (ft_strcmp(tmp, current_path) != 0)
	{
		prev_path = cd_prev_oldpwd(current_path, data);
		if (!prev_path)
			return (free(tmp), -1);
	}
	update_env(current_path, prev_path, data);
	free(prev_path);
	free(current_path);
	return (0);
}

// fonction general qui ouvre le canal de navigation des dossiers
// et gere la lecture du contenu des dossiers. Appelle ensuite "move_to_dir"
// pour changer de dossier
int	cd(char *path, t_env **data)
{
	DIR		*dir;
	char	*new_path;
	char	*tmp;

	if (!path || (path[0] == '~' && path[1] == '\0'))
		return (cd_home(path, data), -1);
	dir = opendir(path);
	if (dir != NULL)
	{
		new_path = getcwd(NULL, 0);
		chdir(path);
		path = getcwd(NULL, 0);
		update_env(new_path, path, data);
		return (free(new_path), free(path), closedir(dir), -1);
	}
	else if (path[0] == '~' && path[1] != '\0')
	{
		tmp = find_in_env("HOME=", (*data)->var);
		path = ft_strjoin(tmp, &path[1]);
		return (cd(path, data), -1);
	}
	else if (path[0] == '-')
		return (cd_prev(path, data), -1);
	else
		return (perror("cd"), -1);
}
