/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:09:11 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/13 10:24:51 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	initiate_struc_envp(t_env **data, char **envp)
{
	*data = malloc(sizeof(t_env));
	if (!data)
		return ;
	count_env(envp, data);
	get_env(envp, data);
}

void	count_env(char **envp, t_env **data)
{
	int	index;
	int	j;
	int	count;

	index = 0;
	j = 0;
	count = 0;
	while (envp[index])
	{
		j = 0;
		while (envp[index][j])
		{
			j++;
			count += j;
		}
		index++;
	}
	count += index;
	(*data)->size = index;
	(*data)->word_count = count;
}

void	get_env(char **envp, t_env **data)
{
	int		index;

	index = 0;
	(*data)->var = NULL;
	(*data)->var = (char **)malloc(sizeof(char *) * (*data)->size + 1);
	if (!(*data)->var)
		return ;
	while (envp[index])
	{
		(*data)->var[index] = ft_strdup(envp[index]);
		index++;
	}
}

void	env(t_env **data)
{
	int		index;

	index = 0;
	while ((*data)->var[index])
	{
		printf("%s\n", (*data)->var[index]);
		index++;
	}
}

char	*find_in_env(char *input, char **env)
{
	int	index;

	index = 0;
	while (env[index])
	{
		if (ft_strncmp(env[index], input, ft_strlen(input)) == 0)
			return (ft_strtrim(env[index], input));
		index++;
	}
	return (NULL);
}
