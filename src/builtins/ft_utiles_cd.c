/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utiles_cd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:48:42 by agiliber          #+#    #+#             */
/*   Updated: 2024/11/05 11:53:38 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Fonction permettant de verifier l'accessibilite d'un dossier
int	handle_new_pwd(char *tmp_new, char *pwd, char *new_path, t_env **data)
{
	if (tmp_new)
	{
		if ((*data)->pwd != NULL)
			free((*data)->pwd);
		(*data)->pwd = ft_strdup(tmp_new);
		if (!(*data)->pwd)
			return (free(tmp_new), -1);
		pwd = ft_strdup("PWD=");
		if (!pwd)
			return (free((*data)->pwd), free(tmp_new), -1);
		new_path = ft_strjoin(pwd, tmp_new);
		if (!new_path)
			return (free((*data)->pwd), free(tmp_new), perror("new_path"), -1);
		if (export_existing("PWD=", data, new_path) == -1)
			return (free((*data)->pwd), free(new_path), free(tmp_new), -1);
		free(new_path);
		free(tmp_new);
		return (0);
	}
	return (-1);
}

int	handle_old_pwd(char *tmp_old, char **old_pwd, char **old_path, t_env **data)
{
	if (tmp_old)
	{
		if ((*data)->old_pwd != NULL)
			free((*data)->old_pwd);
		(*data)->old_pwd = ft_strdup(tmp_old);
		if (!(*data)->old_pwd)
			return (free(tmp_old), -1);
		*old_pwd = ft_strdup("OLDPWD=");
		if (!*old_pwd)
			return (free((*data)->old_pwd), free(tmp_old), -1);
		*old_path = ft_strjoin(*old_pwd, tmp_old);
		if (!*old_path)
			return (free((*data)->old_pwd), free(tmp_old), -1);
		if (export_existing("OLDPWD=", data, *old_path) == -1)
			return (free((*data)->old_pwd), free(*old_path), free(tmp_old), -1);
		free(*old_path);
		free(tmp_old);
	}
	return (-1);
}

// Fonction permettant de mettre a jour les var d'environnement OLDPWD, PWD
// suite a un changement de dossier
int	update_env(char *tmp_old, char *tmp_new, t_env **data)
{
	char	*old_path;
	char	*new_path;
	char	*old_pwd;
	char	*pwd;

	new_path = NULL;
	old_path = NULL;
	pwd = NULL;
	old_pwd = NULL;
	if (handle_new_pwd(tmp_new, pwd, new_path, data) == -1)
		return (-1);
	if (handle_old_pwd(tmp_old, &old_pwd, &old_path, data) == -1)
		return (-1);
	return (0);
}

// Navigation dans un dossier avec un path donne.
int	go_to_path(char *path)
{
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
