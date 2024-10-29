/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:09:11 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/29 08:33:44 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	initiate_struc_envp(t_env **data, char **envp)
{
	char	*pwd;
	char	*oldpwd;

	*data = malloc(sizeof(t_env));
	if (!data)
		return ;
	count_env(envp, data);
	if ((*data)->size != 0)
		get_env(envp, data);
	pwd = find_in_env("PWD=", envp);
	oldpwd = find_in_env("OLDPWD=", envp);
	(*data)->pwd = ft_strdup(pwd);
	(*data)->old_pwd = ft_strdup(oldpwd);
	free(pwd);
	free(oldpwd);
}

void	count_env(char **envp, t_env **data)
{
	int	index;

	index = 0;
	while (envp[index])
	{
		index++;
	}
	(*data)->size = index;
}

void	get_env(char **envp, t_env **data)
{
	int	index;

	index = 0;
	(*data)->var = ft_calloc((*data)->size + 1, sizeof(char *));
	if (!(*data)->var)
		return ;
	while (envp[index])
	{
		(*data)->var[index] = ft_strdup(envp[index]);
		if (!(*data)->var[index])
		{
			free_all((*data)->var);
			(*data)->var = NULL;
			return ;
		}
		index++;
	}
	(*data)->var[index] = NULL;
}

void	env(t_env **data)
{
	int	index;

	index = 0;
	if ((*data)->var == NULL)
	{
		perror("env");
		return ;
	}
	while (index < (*data)->size)
	{
		printf("%s\n", (*data)->var[index]);
		index++;
	}
}

char	*find_in_env(char *input, char **env)
{
	int		index;
	char	*str_trim;

	index = 0;
	while (env[index])
	{
		if (ft_strncmp(env[index], input, ft_strlen(input)) == 0)
		{
			str_trim = ft_strtrim(env[index], input);
			return (str_trim);
		}
		index++;
	}
	return (NULL);
}
