/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:43:21 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/09/18 14:33:18 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	add_count_elem(char **data)
{
	int	i;

	i = 0;
	while (data[i])
			i++;
	return (i);
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

void	add_to_cmd(char *data, t_cmd *current)
{
	int	i;
	char	**new_str;

	i = 0;
	if (current->str)
	{
		while (current->str[i])
			i++;
	}
	new_str = malloc(sizeof(char *) * (i + 2));
	if (!new_str)
		return ;
	i = 0;
	while (current->str && current->str[i])
	{
		new_str[i] = current->str[i];
		i++;
	}
	new_str[i] = ft_strdup(data);
	new_str[i + 1] = NULL;
	free(current->str);
	current->str = new_str;
}

void	add_quotes(char *data, t_cmd *current)
{
	int		i;
	int		j;
	char	**new_str;
	char	**splitted;

	i = 0;
	j = 0;
	if (current->str)
	{
		while (current->str[i])
			i++;
	}
	splitted = ft_split(data, ' ');
	new_str = malloc(sizeof(char *) * (i + ft_array_len(splitted) + 1));
	if (!new_str)
		return ;
	i = 0;
	while (current->str && current->str[i])
	{
		new_str[j] = current->str[i];
		i++;
		j++;
	}
	i = 0;
	while (splitted && splitted[i])
	{
		new_str[j] = ft_strdup(splitted[i]);
		i++;
		j++;
	}
	new_str[j] = NULL;
	free(current->str);
	current->str = new_str;
}

t_cmd	*parser(t_lexer **tokens)
{
	t_cmd	*head;
	t_cmd	*current;
	t_lexer	*tmp;

	tmp = *tokens;
	init_cmd(&head, &current);
	if (!check_synthax_error(tmp))
	{
		while (tmp)
		{
			if (tmp->type == E_CMD || tmp->type == E_OPTIONS
				|| tmp->type == E_ARG)
				add_to_cmd(tmp->data, current);
			else if (tmp->type == E_PIPE)
			{
				current->next = create_new_cmd();
				current->next->prev = current;
				current = current->next;
			}
			else if (tmp->type == E_D_QUOTE || tmp->type == E_S_QUOTE)
			{
				printf("data = %s\n", tmp->data);
					add_quotes(tmp->data, current);
			}
			else if (is_redirection(tmp->type))
			{
				handle_redirection(tmp, current);
				add_to_cmd(tmp->data, current);
			}
			tmp = tmp->next;
		}
	}
	return (head);
}
