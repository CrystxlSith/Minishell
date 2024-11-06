/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utiles_echo2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 09:29:32 by agiliber          #+#    #+#             */
/*   Updated: 2024/11/05 14:13:33 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_all(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

void	free_remaining_tab(char **s, int index)
{
	if (!s)
		return ;
	while (s[index])
	{
		free(s[index]);
		index++;
	}
	free(s);
}

void	free_rest_tab(char **s, int index)
{
	while (index > 0)
	{
		free(s[index]);
		index--;
	}
	free(s);
}

void	print_tab(t_env **data)
{
	int	i;

	i = 0;
	while ((*data)->var[i])
	{
		printf("Tab[%d] : %s\n", i, (*data)->var[i]);
		i++;
	}
}
