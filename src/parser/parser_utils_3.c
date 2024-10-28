/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 16:15:40 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/10/28 08:00:33 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	rep_d(t_lexer *tmp, char *res, t_env **data)
{
	while (tmp)
	{
		if (is_cmd(tmp->type) || tmp->type == E_D_QUOTE)
			replace_dollar(&tmp->data, res, data);
		tmp = tmp->next;
	}
}

void	add_to_cmd(char *data, t_cmd *current)
{
	char	**new_tab;
	int		i;
	int		count;

	count = 0;
	if (current->str)
	{
		while (current->str[count])
			count++;
		new_tab = malloc(sizeof(char *) * (count + 2));
		if (!new_tab)
			return ;
		i = 0;
		while (i < count)
		{
			new_tab[i] = current->str[i];
			i++;
		}
		new_tab[i] = data;
		new_tab[i + 1] = NULL;
		free(current->str);
	}
	else
		new_tab = add_data_to_tab(data);
	current->str = new_tab;
}

char	**env_find(char *input)
{
	int		i;
	int		j;
	int		k;
	char	**env_vars;

	env_vars = malloc(sizeof(char *) * 4096);
	j = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '$')
		{
			k = 0;
			i++;
			while (input[i] && !ft_isspace(input[i]))
			{
				env_vars[j][k] = input[i];
				i++;
			}
			j++;
		}
		i++;
	}
	return (env_vars);
}

int	loop_while_dollar(char **input, char **tmp, int i, char *tmp2)
{
	int		k;
	int		tmp_len;
	char	*new_tmp;

	tmp_len = i;
	k = 0;
	while (ft_isdigit((*input)[i++]) || \
	ft_isalpha((*input)[i]) || (*input)[i] == '?' || (*input)[i] == '_')
		k++;
	new_tmp = malloc(sizeof(char) * (i + 1));
	if (!new_tmp)
		return (0);
	free(*tmp);
	*tmp = new_tmp;
	i = 0;
	while (ft_isdigit((*input)[tmp_len]) || \
	ft_isalpha((*input)[tmp_len]) || (*input)[tmp_len] == '?' || \
	(*input)[tmp_len] == '_')
		(*tmp)[i++] = (*input)[tmp_len++];
	(*tmp)[i] = '\0';
	free(tmp2);
	return (k + 1);
}

char	*build_res(char *res, int i, int j, char **input)
{
	char	*new_res;

	new_res = ft_realloc(res, ft_strlen(res), ft_strlen(res) + 3);
	if (!new_res)
		return (NULL);
	free(res);
	res = new_res;
	res[i] = (*input)[j];
	res[i + 1] = '\0';
	return (res);
}
