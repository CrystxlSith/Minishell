/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycry <crycry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 09:43:38 by agiliber          #+#    #+#             */
/*   Updated: 2024/11/06 21:59:42 by crycry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**realloc_utils(int old_size, char **new_tab, t_env **data, int index)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i <= old_size && j < (*data)->size)
	{
		if (i == index && i + 1 <= old_size)
			i++;
		new_tab[j] = ft_strdup((*data)->var[i]);
		if (!new_tab[j])
			return (free_rest_tab(new_tab, j - 1), NULL);
		i++;
		j++;
	}
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
	ft_free_array((*data)->var);
	return (new_tab);
}

int	unset(char *input, t_env **data)
{
	int		i;
	char	*str;

	if (!*data)
		return (1);
	if (input == NULL)
		return (0);
	i = 0;
	str = find_in_env(input, (*data)->var);
	if (str == NULL || ft_strchr(input, '=') != NULL)
	{
		free(str);
		return (0);
	}
	else
	{
		i = get_index(data, input);
		(*data)->size--;
		(*data)->var = ft_realloc_env_unset((*data)->size, data, i);
		free(str);
	}
	return (0);
}
