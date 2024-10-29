/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 09:43:38 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/28 17:19:16 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**realloc_utils(int old_size, char **new_tab, t_env **data, int index)
{
	int		i;
	int		size;
	int		j;

	i = 0;
	j = 0;
	while (i <= old_size && j < (*data)->size)
	{
		if (i == index && i + 1 <= old_size)
			i++;
		size = ft_strlen((*data)->var[i]);
		new_tab[j] = (char *)malloc(size + 1);
		if (!new_tab[j])
			return (free_rest_tab(new_tab, j - 1), NULL);
		ft_memcpy(new_tab[j], (*data)->var[i], size + 1);
		i++;
		j++;
	}
	new_tab[j] = NULL;
	return (new_tab);
}

char	**ft_realloc_env_unset(int new_size, t_env **data, int index)
{
	int		old_size;
	char	**new_tab;

	if (new_size == 0)
		return (NULL);
	new_tab = ft_calloc((new_size + 1), sizeof(char *));
	if (!new_tab)
		return (NULL);
	old_size = (*data)->size;
	if (old_size > new_size)
		old_size = new_size;
	new_tab = realloc_utils(old_size, new_tab, data, index);
	free_rest_tab((*data)->var, (*data)->size);
	(*data)->var = new_tab;
	return (new_tab);
}

void	unset(char *input, t_env **data)
{
	int		i;
	char	*str;
	int		size;

	i = 0;
	size = 0;
	str = find_in_env(input, (*data)->var);
	if (str == NULL || ft_strchr(input, '=') != NULL)
	{
		free(str);
		return ;
	}
	else
	{
		i = get_index(data, input);
		(*data)->size--;
		(*data)->var = ft_realloc_env_unset((*data)->size, data, i);
		free(str);
	}
}
