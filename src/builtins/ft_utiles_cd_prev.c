/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utiles_cd_prev.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:34:15 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/07 16:38:01 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// change de dossier dans le cas ou le OLDPWD = PWD
// verification de l'accessibilite du dossier puis changement de dossier
char	*cd_prev_oldpwd(char *current_path, t_env **data)
{
	char	*prev_path;

	prev_path = find_in_env("OLDPWD=", (*data)->var);
	if (go_to_path(prev_path) == -1)
		return (free(prev_path), free(current_path), NULL);
	return (prev_path);
}

// Obtenir la taille du nom du dossier a traiter
int	get_dir_len(char *path)
{
	int	len;

	len = 0;
	while (path[len])
		len++;
	while (path[len] != '/')
		len--;
	len--;
	return (len);
}

// Obtenir le bon file_path pour changer de dossier.
// Avec un nom specifique de dossier ou un simple retour en arriere.
char	*cd_get_prev_path(char *path, char *current_path)
{
	char	*prev_path;
	int		len;
	int		size;
	char	*tmp;

	len = get_dir_len(current_path);
	if (ft_strncmp(path, "..", 2) == 0)
	{
		prev_path = malloc(sizeof(char) * (len + 1));
		if (!prev_path)
			return (free(current_path), NULL);
		prev_path = ft_strncpy(prev_path, current_path, len + 1);
	}
	else
	{
		tmp = ft_strtrim(path, "../");
		size = get_dir_len(path) + len;
		prev_path = malloc(sizeof(char) * (size + 1));
		if (!prev_path)
			return (free(current_path), NULL);
		prev_path = ft_strncpy(prev_path, current_path, len);
		prev_path = ft_strjoin(prev_path, tmp);
		free(tmp);
	}
	return (prev_path);
}

// change de dossier dans le cas d'un retour dans un dossier precedant
// verification de l'accessibilite du dossier puis changement de dossier
char	*cd_prev_newpwd(char *path, char *current_path)
{
	char	*prev_path;

	prev_path = cd_get_prev_path(path, current_path);
	if (!prev_path)
		return (free(prev_path), free(current_path), NULL);
	if (go_to_path(prev_path) == -1)
		return (free(prev_path), free(current_path), NULL);
	return (prev_path);
}
