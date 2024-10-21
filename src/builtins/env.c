/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:09:11 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/21 15:18:39 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	initiate_struc_envp(t_env **data, char **envp)
{
	*data = malloc(sizeof(t_env));
	if (!data)
		return ;
	count_env(envp, data);
	if ((*data)->size != 0)
		get_env(envp, data);
	(*data)->pwd = find_in_env("PWD=", envp);
	(*data)->old_pwd = find_in_env("OLDPWD=", envp);
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
	(*data)->var = (char **)malloc(sizeof(char *) * ((*data)->size + 1));
	if (!(*data)->var)
		return ;
	while (envp[index])
	{
		(*data)->var[index] = envp[index];
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
