/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utiles_cd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:48:42 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/13 11:23:27 by agiliber         ###   ########.fr       */
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
	if (chdir(path) == -1)
	{
		perror("Cant find Dir");
		return (-1);
	}
	else
		return (TRUE);
}
