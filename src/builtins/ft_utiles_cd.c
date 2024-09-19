/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utiles_cd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:48:42 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/19 17:03:36 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Fonction permettant de verifier l'accessibilite d'un dossier
int	file_compliant(char *dir_path)
{
	if (!opendir(dir_path))
		return (TRUE);
	return (perror("Dir"), FALSE);
}

// Fonction permettant de mettre a jour les var d'environnement OLDPWD, PWD
// suite a un changement de dossier
void	update_env(char *tmp_old, char *tmp_new, t_env **data)
{
	char	*old_path;
	char	*new_path;

	old_path = ft_strjoin("OLDPWD=", tmp_old);
	new_path = ft_strjoin("PWD=", tmp_new);
	export(old_path, data);
	export(new_path, data);
}

// Navigation dans un dossier avec un path donne.
int	go_to_path(char *path)
{
	print_env();
	printf("My path : %s\n", path);
	if (chdir(path) == -1)
	{
		perror("Cant find Dir");
		return (-1);
	}
	else
		return (TRUE);
}

// Modifie le path dans le bon format
char	*format_dir_path(char *path)
{
	char	*new_path;
	int		len;

	if (!path)
		return (path);
	len = ft_strlen(path);
	if (ft_strncmp(path, "./", 2) == 0)
		new_path = ft_strtrim(path, "./");
	else if (path[len] == '/')
		new_path = ft_strtrim(path, "/");
	else if (ft_strncmp(path, "./", 2) == 0 && path[len] == '/')
	{
		new_path = ft_strtrim(path, "./");
		new_path = ft_strtrim(path, "/");
	}
	else
		return (path);
	return (new_path);
}

// Definit quelle fonction de deplacement de dossier faire
char	*move_to_dir(char *path, t_env **data)
{
	printf("PATH %s\n", path);
	if (path == NULL || ft_strcmp(path, "") == 0)
		return (cd_home(path, data));
	else if (ft_strncmp(path, "../", 3) == 0
		|| ft_strncmp(path, "..", 2) == 0)
		return (cd_prev(path, data));
	else if (path != NULL || ft_strncmp(path, "./", 2) == 0)
		return (cd_next(path, data));
	return (NULL);
}
