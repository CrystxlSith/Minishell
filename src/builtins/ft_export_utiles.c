/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utiles.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:15:42 by agiliber          #+#    #+#             */
/*   Updated: 2024/11/05 14:36:58 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* // Realloc de la memoire avec l'ajout et la suppression de variables d'env
char	**ft_realloc_env(int new_size, t_env **data)
{
	int		old_size;
	char	**new_tab;
	int		i;
	int		size;

	if (new_size == 0)
		return (NULL);
	new_tab = ft_calloc(new_size + 1, sizeof(char *));
	if (!new_tab)
		return (NULL);
	old_size = (*data)->size;
	if (old_size > new_size)
		old_size = new_size;
	i = 0;
	while (i < old_size)
	{
		size = ft_strlen((*data)->var[i]);
		new_tab[i] = ft_calloc((size + 1), sizeof(char));
		if (!new_tab[i])
			return (free_rest_tab(new_tab, i - 1), NULL);
		ft_memcpy(new_tab[i], (*data)->var[i], size + 1);
		i++;
	}
	free_all((*data)->var);
	return ((*data)->var = new_tab, new_tab);
} */

// Realloc de la memoire avec l'ajout et la suppression de variables d'env
char	**ft_realloc_env(int new_size, t_env **data)
{
	int		old_size;
	char	**new_tab;
	int		i;
	int		size;

	if (new_size == 0)
		return (NULL);
	new_tab = ft_calloc(new_size + 1, sizeof(char *));
	if (!new_tab)
		return (NULL);
	old_size = (*data)->size;
	if (old_size > new_size)
		old_size = new_size;
	i = 0;
	while (i < old_size)
	{
		size = ft_strlen((*data)->var[i]);
		new_tab[i] = ft_strdup((*data)->var[i]);
		if (!new_tab[i])
			return (free_rest_tab(new_tab, i - 1), NULL);
		i++;
	}
	free_all((*data)->var);
	return (new_tab);
}

// Dans le cas ou la var d'envp existe deja, cherche la var dans
// le tableau d'environnement. Une fois trouve, la remplace par
// la valeur donne en input
int	export_existing(char *flag, t_env **data, char *cmd)
{
	int	i;

	i = get_index(data, flag);
	if (i == -1)
		return (-1);
	free((*data)->var[i]);
	(*data)->var[i] = ft_strdup(cmd);
	return (0);
}

// Duplique le tableau d'environement dans le tableau realloue, en ajoutant
// a la fin la nouvelle variable. Met a jour la variable "size" de la structure.
void	duplicate_env(t_env **data, char *cmd)
{
	int	i;

	i = 0;
	while (i < (*data)->size)
		i++;
	if (cmd != NULL)
	{
		(*data)->var[i] = ft_strdup(cmd);
		if (!(*data)->var[i])
		{
			free_all((*data)->var);
			free(cmd);
			return ;
		}
		(*data)->size++;
	}
}

// Dans le cas ou la var d'envp n'existe pas, realloue de la memoire pour
// ajouter une ligne dans le tableau d'envp, puis duplique l'envp avec
// la nouvelle variable a ajouter.
void	export_new(t_env **data, char *cmd)
{
	int		size;

	size = (*data)->size;
	(*data)->var = ft_realloc_env(size + 2, data);
	if (!(*data)->var)
	{
		free(cmd);
		return ;
	}
	duplicate_env(data, cmd);
}

// En fonction de si la variable existe deja dans le tableau d'environnement
// la fonctionne redirige la commande pour ajout ou modification du tableau
int	update_env_tab_export(char *flag, char *cmd, t_env **data)
{
	int		target;

	if (!flag)
		return (-1);
	if (!(*data)->var)
		export_new(data, cmd);
	else
	{
		target = get_index(data, flag);
		if (target != -1)
			export_existing(flag, data, cmd);
		else
			export_new(data, cmd);
	}
	return (0);
}
