/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 09:43:38 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/01 10:02:28 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	unset(char *input, t_env **data)
{
	char	**new_env;
	int		i;

	i = 0;
	new_env = NULL;
	if (find_in_env(input, (*data)->var) != NULL)
		flag = find_in_env(input, (*data)->var);
	else
	{
		perror("unset");
		return ;
	}
	else
	{
		i = get_index(data, input);
		(*data)->var[i] = NULL;
		free((*data)->var[i]);
		(*data)->size--;
		new_env = ft_realloc_env((*data)->size, data);
	}
}
