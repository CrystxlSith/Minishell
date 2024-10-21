/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 09:43:38 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/21 11:51:07 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_realloc_env_unset(int new_size, t_env **data, int index)
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
	i = -1;
	while (++i < old_size)
	{
		if (i == index && (*data)->var[i + 1] != NULL)
			i++;
		size = ft_strlen((*data)->var[i]);
		new_tab[i] = (char *)malloc(size + 1);
		if (!new_tab[i])
			return (free_rest_tab(new_tab, i - 1), NULL);
		ft_memcpy(new_tab[i], (*data)->var[i], size + 1);
	}
	return (new_tab[old_size] = NULL, new_tab);
}

void	unset(char *input, t_env **data)
{
	char	**new_env;
	int		i;
	char	*str;

	i = 0;
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
		(*data)->var[i] = NULL;
		free((*data)->var[i]);
		(*data)->size--;
		new_env = ft_realloc_env_unset((*data)->size, data, i);
		free(str);
		free_all(new_env);
	}
}
