/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:09:11 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/06 14:47:56 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	count_env(char **envp, t_env **data)
{
	int		index;

	index = 0;
	while (envp[index])
	{
		index++;
	}
	(*data)->size = index;
}


void	get_env(char **envp, t_env **data)
{
	int		index;

	index = 0;
	count_env(envp, data);
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

void	env(char **envp)
{
	t_env	*data;
	int		index;

	index = 0;
	data = malloc(sizeof(t_env));
	if (!data)
		return ;
	get_env(envp, &data);
	while (data->var[index])
	{
		printf("%s\n", data->var[index]);
		index++;
	}
}

char	*find_environment(char **input, char **envp)
{
	int		i;
	int		index;
	char	*str;
	char	*tmp;
	char	*final_str;

	str = NULL;
	i = get_index(input, "$");
	printf("i : %d\n", i);
	str = ft_strtrim(input[i], "$");
	if (!str)
		return (NULL);
	printf("STR : %s\n", str);
	index = find_line(envp, str);
	printf("index : %d\n", index);
	if (!index)
		return (free(str), NULL);
	printf("ENVP : %s\n", envp[index]);
	tmp = ft_strdup(envp[index]);
	if (!tmp)
		return (free(str), NULL);
	final_str = ft_strtrim(tmp, str);
	free(tmp);
	free(str);
	return (final_str);
}
