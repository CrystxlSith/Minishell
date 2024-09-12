/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:07:33 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/12 14:35:26 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// fonction pour revenir a la base des dossiers du user
void	cd_home(char *path, t_env **data)
{
	char	*new_path;
	char	*old_path;
	char	*tmp;

	path = getenv("HOME");
	if (!path)
	{
		printf("%s\n", "No HOME configured");
		return ;
	}
	tmp = getcwd(NULL, 0);
	old_path = ft_strjoin("OLDPWD=", tmp);
	free(tmp);
	go_to_path(path);
	new_path = ft_strjoin("PWD=", getcwd(NULL, 0));
	update_env(old_path, new_path, data);
	free(old_path);
	free(new_path);
}

// fonction pour entrer dans le dossier suivant de son choix
void	cd_next(char *path, t_env **data)
{
	char	*next_path;
	char	*current_path;
	char	*tmp;

	if (go_to_path(path) == 0)
		return ;
	current_path = getcwd(NULL, 0);
	tmp = ft_strjoin(current_path, "/");
	next_path = ft_strjoin(tmp, path);
	free(tmp);
	if (file_compliant(next_path) == FALSE)
	{
		free(next_path);
		return ;
	}
	go_to_path(next_path);
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

	if (go_to_path(path) == 0)
		return ;
	len = 0;
	current_path = getcwd(NULL, 0);
	if (ft_strcmp(getenv("OLDPWD"), current_path) != 0)
	{
		prev_path = cd_prev_oldpwd(current_path);
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
	if (path == NULL || ft_strcmp(path, "") == 0)
		cd_home(path, data);
	else if (ft_strncmp(path, "../", 3) == 0
		|| ft_strncmp(path, "..", 2) == 0)
		cd_prev(path, data);
	else if (path != NULL || ft_strncmp(path, "./", 2) == 0)
		cd_next(path, data);
}
