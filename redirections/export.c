/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:27:49 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/06 16:53:14 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_realloc(char **tab, int new_size, t_env **data)
{
	int		old_size;
	char	**new_tab;
	int		i;

	if (new_size == 0)
		return (free_all(tab), NULL);
	if (tab == NULL)
		return (tab = (char **)malloc(sizeof(char *) * new_size + 1), NULL);
	new_tab = (char **)malloc(sizeof(char *) * new_size + 1);
	if (!new_tab)
		return (NULL);
	old_size = (*data)->size;
	if (old_size > new_size)
		old_size = new_size;
	i = 0;
	while (tab[i])
	{
		new_tab[i] = ft_strdup(tab[i]);
		i++;
	}
	(*data)->size = new_size + 1;
	free_all(tab);
	return (new_tab);
}

void	export(char **input, t_env **data)
{
	int		index;
	int		i;
	char	*cmd;
	char	**new_tab;

	index = get_index(input, "AGT=");
	i = 0;
	cmd = ft_strdup(input[index]);
	if (!cmd)
		return ;
	while (i < (*data)->size)
		i++;
	new_tab = ft_realloc((*data)->var, i + 1, data);
	if (!new_tab)
		return ;
	(*data)->var = new_tab;
	(*data)->var[i] = ft_strdup(cmd);
	index = 0;
	while ((*data)->var[index])
	{
		printf("%s\n", (*data)->var[index]);
		index++;
	}
	free(cmd);
}
