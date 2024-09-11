/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:27:49 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/11 10:37:21 by agiliber         ###   ########.fr       */
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

	i = get_index(data, flag);
	free((*data)->var[i]);
	(*data)->var[i] = ft_strdup(cmd);
	index = 0;
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
	duplicate_env(data, new_tab, cmd);
	print_tab(data);
}

void	export(char **input, t_env *data)
{
	char	*cmd;
	int		index;
	char	*flag;
	int		target;

	flag = "AGT=";
	index = 2;
	cmd = ft_strdup(input[index]);
	if (!cmd)
		return ;
	print_tab(&data);
	printf("CMD : %s\n", cmd);
	printf("Flag : %s\n", flag);
	printf("Size : %d\n", (data)->size);
	target = get_index(&data, flag);
	printf("target : %d\n", target);
	printf("signal : %d\n", signal);
	if (target != -1)
	{
		signal++;
		printf("%s\n", "Existing");
		export_existing(flag, &data, cmd);
	}
	else
	{
		signal++;
		printf("%s\n", "New");
		export_new(&data, cmd);
	}
}
