/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 09:56:28 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/11 10:12:21 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_lst(t_dirent **dir)
{
	t_dirent	*tmp;

	tmp = *dir;
	while (tmp != NULL)
	{
		printf("file_name : %s\n", (*dir)->file_name);
		printf("current_path : %s\n", (*dir)->current_path);
		printf("previous_path : %s\n", (*dir)->previous_path);
		printf("home_path : %s\n", (*dir)->home_path);
		printf("type : %s\n", (*dir)->type);
		tmp = tmp->next;
	}
}
