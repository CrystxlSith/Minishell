/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 09:43:38 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/18 13:52:50 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		new_env = ft_realloc_env((*data)->size, data);
		free(str);
		free_all(new_env);
	}
}
