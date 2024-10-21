/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 09:43:38 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/21 15:22:10 by agiliber         ###   ########.fr       */
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
		if (i == index)
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
	new_tab = (char **)malloc(sizeof(char *) * (new_size + 1));
	if (!new_tab)
		return (NULL);
	old_size = (*data)->size;
	if (old_size > new_size)
		old_size = new_size;
	new_tab = realloc_utils(old_size, new_tab, data, index);
	(*data)->size--;
	return (new_tab);
}

void	unset(char *input, t_env **data)
{
	char	**new_env;
	int		i;
	char	*str;
	int		size;

	i = 0;
	size = 0;
	str = find_in_env(input, (*data)->var);
	if (str == NULL || ft_strchr(input, '=') != NULL)
	{
		perror("unset");
		free(str);
		return ;
	}
	else
	{
		i = get_index(data, input);
		size = (*data)->size - 1;
		new_env = ft_realloc_env_unset(size, data, i);
		(*data)->var = new_env;
		free(str);
	}
}
