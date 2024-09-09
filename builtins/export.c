/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:27:49 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/09 15:11:28 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	export_existing(char *flag, t_env **data, char *cmd)
{
	int	i;
	int	index;

	i = get_index((*data)->var, flag);
	free((*data)->var[i]);
	(*data)->var[i] = ft_strdup(cmd);
	index = 0;
/* 	while ((*data)->var[index])
	{
		printf("Existing : %s\n", (*data)->var[index]);
		index++;
	} */
	free(cmd);
	return ;
}

void	duplicate_env(t_env **data, char **input, char *cmd)
{
	int	i;

	i = 0;
	while (input[i])
	{
		(*data)->var[i] = ft_strdup(input[i]);
		i++;
	}
	(*data)->var[i] = ft_strdup(cmd);
	(*data)->var[i + 1] = NULL;
	(*data)->size++;
	i = 0;
	while (i < (*data)->size)
	{
		printf("New tab[%d] : %s\n", i, (*data)->var[i]);
		i++;
	}
	free(cmd);
	free_all(input);
}

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
	(*data)->var = new_tab;
	duplicate_env(data, (*data)->var, cmd);
}

void	export(char **input, t_env **data)
{
	char	*cmd;
	int		index;
	char	*flag;
	int		target;

	flag = "AGT=";
	index = get_index(input, flag);
	if (index < 0)
		return ;
	cmd = ft_strdup(input[index]);
	if (!cmd)
		return ;
	printf("Flag : %s\n", flag);
	printf("Index : %d\n", get_index((*data)->var, flag));
	printf("Size : %d\n", (*data)->size);
	target = get_index((*data)->var, flag);
	if (target != -1)
	{
		printf("%s\n", "Existing");
		export_existing(flag, data, cmd);
	}
	else
	{
		printf("%s\n", "New");
		export_new(data, cmd);
	}
}
