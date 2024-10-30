/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycry <crycry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:38:32 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/10/30 14:45:50 by crycry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**add_data_to_tab(char *data)
{
	char	**new_tab;

	new_tab = malloc(sizeof(char *) * 2);
	if (!new_tab)
		return (NULL);
	new_tab[0] = data;
	new_tab[1] = NULL;
	return (new_tab);
}

void	init_temp(char **tmp, char **tmp2)
{
	*tmp = malloc(sizeof(char) * 4096);
	if (!*tmp)
		return ;
	*tmp2 = malloc(sizeof(char) * 4096);
	if (!*tmp2)
		return ;
	(*tmp)[0] = '\0';
	(*tmp2)[0] = '\0';
}

int	handle_number(char **input, int *i, char *tmp, char *tmp2)
{
	(*i)++;
	if ((*input)[*i] >= '1' && (*input)[*i] <= '9')
	{
		(*i)++;
		free(tmp);
		free(tmp2);
		return (1);
	}
	return (0);
}

void	fill_nbr_element(t_cmd **parsing)
{
	t_cmd	*tmp;

	tmp = *parsing;
	while (tmp != NULL)
	{
		tmp->elem_nb = add_count_elem(tmp->str);
		tmp = tmp->next;
	}
}

void	handle_env_value(char **res, char *tmp, int *i, t_env **data)
{
	char	*env_value;
	char	*new_res;

	if (tmp)
	{
		tmp = ft_strjoin(ft_strdup(tmp), "=");
		env_value = find_in_env(tmp, (*data)->var);
		if (env_value)
		{
			new_res = ft_strjoin(*res, env_value);
			*res = new_res;
			*i += ft_strlen(env_value);
			free(env_value);
		}
		free(tmp);
	}
}
