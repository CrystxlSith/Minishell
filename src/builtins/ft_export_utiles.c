/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utiles.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:15:42 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/16 10:09:08 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Realloc de la memoire avec l'ajout et la suppression de variables d'env
char	**ft_realloc(int new_size, t_env **data)
{
	int		old_size;
	char	**new_tab;
	int		i;
	int		size;

	if (new_size == 0)
		return (NULL);
	new_tab = (char **)malloc(sizeof(char *) * (new_size + 1));
	if (!new_tab)
		return (NULL);
	old_size = (*data)->size;
	if (old_size > new_size)
		old_size = new_size;
	i = 0;
	while (i < old_size)
	{
		size = ft_strlen((*data)->var[i]);
		new_tab[i] = (char *)malloc(size + 1);
		if (!new_tab[i])
			return (free_rest_tab(new_tab, i - 1), NULL);
		ft_memcpy(new_tab[i], (*data)->var[i], size + 1);
		i++;
	}
	new_tab[new_size] = NULL;
	return (new_tab);
}

// Dans le cas ou la var d'envp existe deja, cherche la var dans
// le tableau d'environnement. Une fois trouve, la remplace par
// la valeur donne en input
void	export_existing(char *flag, t_env **data, char *cmd)
{
	int	i;
	int	index;

	i = get_index(data, flag);
	free((*data)->var[i]);
	(*data)->var[i] = ft_strdup(cmd);
	index = 0;
	free(cmd);
	return ;
}

// Duplique le tableau d'environement dans le tableau realloue, en ajoutant
// a la fin la nouvelle variable. Met a jour la variable "size" de la structure.
void	duplicate_env(t_env **data, char **input, char *cmd)
{
	int	i;

	i = 0;
	while (input[i] && i < (*data)->size)
	{
		(*data)->var[i] = ft_strdup(input[i]);
		i++;
	}
	if (cmd != NULL)
	{
		(*data)->var[i] = ft_strdup(cmd);
		(*data)->var[i + 1] = NULL;
		(*data)->size++;
		free(cmd);
	}
	free_all(input);
}

// Dans le cas ou la var d'envp n'existe pas, realloue de la memoire pour
// ajouter une ligne dans le tableau d'envp, puis duplique l'envp avec
// la nouvelle variable a ajouter.
void	export_new(t_env **data, char *cmd)
{
	char	**new_tab;
	int		size;

	size = (*data)->size;
	new_tab = ft_realloc(size + 2, data);
	if (!new_tab)
	{
		free(cmd);
		return ;
	}
	duplicate_env(data, new_tab, cmd);
}

// En fonction de si la variable existe deja dans le tableau d'environnement
// la fonctionne redirige la commande pour ajout ou modification du tableau
void	update_env_tab_export(char *flag, char *cmd, t_env **data)
{
	int		target;

	target = get_index(data, flag);
	if (target != -1)
	{
		export_existing(flag, data, cmd);
		flag = ft_strtrim(flag, "=");
	}
	else
		export_new(data, cmd);
}
