/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_hdc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycry <crycry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:04:40 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/30 14:42:08 by crycry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	loop_while_dollar_hdc(char **input, char **tmp, int i, char *tmp2)
{
	int	k = 0;
	int	tmp_len = i;
	char *new_tmp;

	if (!(*input)[i + 1])
	{
		free(*tmp);
		free(tmp2);
		return 0;
	}
	while (ft_isdigit((*input)[i]) || ft_isalpha((*input)[i]) || (*input)[i] == '?' || (*input)[i] == '_')
	{
		k++;
		i++;
	}
	new_tmp = malloc(sizeof(char) * (k + 1));
	if (!new_tmp)
		return 0;
	free(*tmp);
	*tmp = new_tmp;
	i = 0;
	while (ft_isdigit((*input)[tmp_len]) || ft_isalpha((*input)[tmp_len]) || (*input)[tmp_len] == '?' || (*input)[tmp_len] == '_')
		(*tmp)[i++] = (*input)[tmp_len++];
	(*tmp)[i] = '\0';
	free(tmp2);
	return (k);
}

void	replace_dollar_hdc(char **input, t_env **data)
{
	int		i;
	int		j;
	char	*tmp;
	char	*tmp2;
	char    *res;

	init_replace_dollar(&i, &j, &res);
	if (*input)
	{
		while ((*input)[j])
		{
			init_temp(&tmp, &tmp2);
			if ((*input)[j] == '$' && (*input)[j + 1] != '?')
			{
				if (!(*input)[j + 1])
				{
					j++;
					free(tmp);
					free(tmp2);
					continue ;
				}
				if (handle_number(input, &j, tmp, tmp2))
					continue ;
				j += loop_while_dollar_hdc(input, &tmp, j, tmp2);
				handle_env_value(&res, tmp, &i, data);
			}
			else
			{
				handle_question(&res, &i, input, &j);
				res = build_res(res, i, j, input);
				//free_increment(&tmp, &tmp2, &i, &j);
			}
		}
		free(*input);
		*input = res;
	}
}
