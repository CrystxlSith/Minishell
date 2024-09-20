/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 09:43:38 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/18 10:53:02 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	unset(char *input, t_env **data)
{
	char	**new_env;
	char	*flag;
	int		i;

	i = 0;
	if (find_in_env(input, (*data)->var) != NULL)
		flag = ft_strdup(input);
	else
	{
		flag = ft_strjoin(input, "=");
		if (!flag)
			return ;
	}
	if (find_in_env(flag, (*data)->var) != NULL)
	{
		i = get_index(data, flag);
		(*data)->var[i] = NULL;
		free((*data)->var[i]);
		(*data)->size--;
		new_env = ft_realloc((*data)->size, data);
		duplicate_env(data, new_env, NULL);
	}
	free(flag);
}
