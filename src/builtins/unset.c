/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 09:43:38 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/27 10:12:14 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	unset(char *input, t_env **data)
{
	char	**new_env;
	char	*flag;
	int		i;

	i = 0;
	new_env = NULL;
	if (find_in_env(input, (*data)->var) != NULL)
		flag = find_in_env(input, (*data)->var);
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
		new_env = ft_realloc_env((*data)->size, data);
	}
	free(flag);
}
