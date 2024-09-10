/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:07:33 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/10 15:04:14 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_previous_path(char **envp)
{
	int		index;
	char	*old_path;

	index = 0;
	while (envp[index])
	{
		if (ft_strncmp(envp[index], "OLDPWD=", 8) == 0)
		{
			old_path = ft_strtrim(envp[index], "OLDPWD=");
			if (!old_path)
				return (NULL);
			return (old_path);
		}
		index++;
	}
	return (NULL);
}

void	initiate_dir_list(t_dirent **dir)
{
	(*dir)->file_name = NULL;
	(*dir)->current_path = NULL;
	(*dir)->previous_path = NULL;
	(*dir)->type = NULL;
	(*dir)->next = NULL;
	(*dir)->previous = NULL;
}

void	fill_dir_list(t_dirent **dir, char **envp)
{
	(*dir)->current_path = getcwd(NULL, 0);
	(*dir)->previous_path = get_previous_path(envp);
}

void	cd(char	**path)
{

}