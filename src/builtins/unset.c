/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: mariannedubuard <mariannedubuard@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 09:43:38 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/30 11:41:14 by mariannedub      ###   ########.fr       */
=======
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 09:43:38 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/27 10:12:14 by kali             ###   ########.fr       */
>>>>>>> e230fa8f0608e785cc07771d7c7705d805deaa29
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	unset(char *input, t_env **data)
{
	char	**new_env;
	int		i;

	i = 0;
<<<<<<< HEAD
	if (find_in_env(input, (*data)->var) == NULL || ft_strchr(input, '=') != NULL)
=======
	new_env = NULL;
	if (find_in_env(input, (*data)->var) != NULL)
		flag = find_in_env(input, (*data)->var);
	else
>>>>>>> e230fa8f0608e785cc07771d7c7705d805deaa29
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
