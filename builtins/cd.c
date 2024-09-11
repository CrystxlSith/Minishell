/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:07:33 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/11 10:26:16 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_home_path(char **envp)
{
	int		index;
	char	*home_path;

	index = 0;
	while (envp[index])
	{
		if (ft_strncmp(envp[index], "HOME=", 5) == 0)
		{
			home_path = ft_strtrim(envp[index], "HOME=");
			if (!home_path)
				return (NULL);
			return (home_path);
		}
		index++;
	}
	return (NULL);
}

char	*get_previous_path(char **envp)
{
	int		index;
	char	*old_path;

	index = 0;
	old_path = NULL;
	while (envp[index])
	{
		if (ft_strncmp(envp[index], "OLDPWD=", 7) == 0)
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

void	fill_dir_list(t_dirent **dir, char **envp)
{
	(*dir)->current_path = getcwd(NULL, 0);
	(*dir)->previous_path = get_previous_path(envp);
	(*dir)->home_path = get_home_path(envp);
}

void	initiate_dir_list(t_dirent **dir)
{
	*dir = malloc(sizeof(t_dirent));
	if (!dir)
		return ;
	(*dir)->file_name = NULL;
	(*dir)->current_path = NULL;
	(*dir)->previous_path = NULL;
	(*dir)->home_path = NULL;
	(*dir)->type = NULL;
	(*dir)->next = NULL;
	(*dir)->previous = NULL;

}

char	*file_compliant(char **av)
{
	char	*file_name;

	if (ft_strncmp(av[2], "../", 3) == 0)
		file_name = ft_strtrim(av[1], "../");
	else
		file_name = av[2];
	if (!opendir(file_name))
		return (file_name);
	return (perror(NULL), NULL);
}

void	cd(int ac, char	**av, t_dirent **dir, t_env **data)
{
	fill_dir_list(dir, (*data)->var);
	print_lst(dir);
	printf("%s %s\n", av[1], av[2]);
	if (ft_strncmp(av[2], "..", 3) == 0)
		chdir((*dir)->previous_path);
	if (ac == 2)
		chdir((*dir)->home_path);
	if (!file_compliant(av))
		chdir(file_compliant(av));
}
