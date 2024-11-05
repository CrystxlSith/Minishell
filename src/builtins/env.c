/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:09:11 by agiliber          #+#    #+#             */
/*   Updated: 2024/11/05 14:28:33 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	initiate_env_supp(t_env **data)
{
	*data = malloc(sizeof(t_env));
	if (!data)
		return (-1);
	(*data)->var = NULL;
	(*data)->pwd = NULL;
	(*data)->old_pwd = NULL;
	(*data)->exit_code = 0;
	return (0);
}

int	initiate_struc_envp(t_env **data, char **envp)
{
	char	*pwd;
	char	*oldpwd;

	*data = malloc(sizeof(t_env));
	if (!data)
		return (-1);
	count_env(envp, data);
	if ((*data)->size != 0)
		get_env(envp, data);
	(*data)->pwd = NULL;
	(*data)->old_pwd = NULL;
	(*data)->exit_code = 0;
	pwd = find_in_env("PWD=", envp);
	if (pwd == NULL)
		return (-1);
	oldpwd = find_in_env("OLDPWD=", envp);
	if (oldpwd == NULL)
		return (free(pwd), -1);
	(*data)->pwd = ft_strdup(pwd);
	(*data)->old_pwd = ft_strdup(oldpwd);
	return (free(pwd), free(oldpwd), 0);
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

int	env(t_env **data)
{
	int	index;

	index = 0;
	if (!*data)
		return (-1);
	if ((*data)->var == NULL)
		return (1);
	while (index < (*data)->size)
	{
		printf("%s\n", (*data)->var[index]);
		index++;
	}
	return (0);
}

char	*find_in_env(char *input, char **env)
{
	int		index;
	char	*str_trim;

	index = 0;
	if (!**env)
		return (NULL);
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
