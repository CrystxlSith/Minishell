/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:43:21 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/09/20 14:41:58 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	add_quotes(char *data, t_cmd *current)
{
	int		i;
	int		j;
	char	**new_str;
	char	**splitted;

	i = 0;
	j = 0;
	printf("data: %s\n", data);
	splitted = ft_split(data, ' ');
	while (current->str && current->str[i])
		i++;
	new_str = malloc(sizeof(char *) * (i + ft_array_len(splitted) + 1));
	if (!new_str)
		return ;
	i = 0;
	while (current->str && current->str[i])
		new_str[j++] = current->str[i++];
	i = 0;
	while (splitted && splitted[i])
		new_str[j++] = ft_strdup(splitted[i++]);
	new_str[j] = NULL;
	free(current->str);
	current->str = new_str;
}

static void	add_to_cmd(char *data, t_cmd *current)
{
	int		i;
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

void	replace_dollar(char **input, t_env **data)
{
	int		i;
	char	*tmp;
	char	*env_var;

	i = 0;
	while ((*input)[i])
	{
		if ((*input)[i] == '$')
		{
			tmp = ft_strtrim(*input, "$");
			tmp = ft_strjoin(tmp, "=");
			env_var = find_in_env(tmp, (*data)->var);
			*input = ft_strdup(env_var);
			free(tmp);
			free(env_var);
		}
		i++;
	}
}

static void	cmd_adding(t_lexer *tmp, t_cmd *current, t_env **data)
{
	while (tmp)
	{
		if (tmp->type == E_CMD || tmp->type == E_OPTIONS || \
			tmp->type == E_ARG)
			replace_dollar(&tmp->data, data);
		if (tmp->type == E_CMD || tmp->type == E_OPTIONS || \
			tmp->type == E_ARG || is_redirection(tmp->type))
			add_to_cmd(tmp->data, current);
		else if (tmp->type == E_PIPE)
		{
			current->next = create_new_cmd();
			current->next->prev = current;
			current = current->next;
		}
		else if (tmp->type == E_D_QUOTE || tmp->type == E_S_QUOTE)
		{
			if (tmp->type == E_D_QUOTE)
				replace_dollar(&tmp->data, data);
			add_quotes(tmp->data, current);
		}
		if (is_redirection(tmp->type))
			handle_redirection(tmp, current);
		tmp = tmp->next;
	}
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

t_cmd	*parser(t_lexer **tokens, t_env **data)
{
	t_cmd	*head;
	t_cmd	*current;
	t_lexer	*tmp;

	tmp = *tokens;
	init_cmd(&head, &current);
	cmd_adding(tmp, current, data);
	return (head);
}
