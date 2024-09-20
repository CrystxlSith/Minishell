/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:43:21 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/09/20 15:47:12 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// static void	add_quotes(char *data, t_cmd *current)
// {
// 	if (current->str)
// 	{
// 		current->str[0] = ft_strjoin(current->str[0], data);
// 	}
// 	else
// 	{
// 		current->str = malloc(sizeof(char *) * 2);
// 		current->str[0] = ft_strdup(data);
// 		current->str[1] = NULL;
// 	}
// }

static void	add_to_cmd(char *data, t_cmd *current)
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
		new_tab[i] = ft_strdup(data);
		new_tab[i + 1] = NULL;
		free(current->str);
	}
	else
	{
		new_tab = malloc(sizeof(char *) * 2);
		if (!new_tab)
			return ;
		new_tab[0] = ft_strdup(data);
		new_tab[1] = NULL;
	}
	current->str = new_tab;
}

char	**env_find(char *input)
{
	int		i;
	int	j;
	int		k;
	char	**env_vars;
	
	env_vars = malloc(sizeof(char *) * 100);
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
			printf("new_input: %s\n", env_vars[j]);
			j++;
		}
		i++;
	}
	return (env_vars);
}

void	replace_dollar(char **input)
{
	int		i;
	int		j;
	int		k;
	int		l;
	char	*new_input;
	char	*tmp;
	char	*env_value;

	i = 0;
	k = 0;
	new_input = malloc(sizeof(char) * (ft_strlen(*input) + 1));
	if (!new_input)
		return ;
	while ((*input)[i])
	{
		if ((*input)[i - 1] && (*input)[i] == '$' && ft_isspace((*input)[i - 1]))
		{
			tmp = malloc(sizeof(char) * (ft_strlen(*input) - i + 1));
			if (!tmp)
				return ;
			l = 0;
			i++;
			while ((*input)[i] && (ft_isalnum((*input)[i]) || (*input)[i] == '_'))
			{
				tmp[l++] = (*input)[i++];
			}
			tmp[l] = '\0';
			env_value = getenv(tmp);
			free(tmp);
			if (env_value)
			{
				j = 0;
				while (env_value[j])
					new_input[k++] = env_value[j++];
			}
		}
		else
			new_input[k++] = (*input)[i++];
	}
	new_input[k] = '\0';
	free(*input);
	*input = new_input;
}

void	new_cmd(t_cmd **current)
{
		(*current)->next = create_new_cmd();
		(*current)->next->prev = *current;
		*current = (*current)->next;
}

void	new_quote_cmd(t_lexer *tmp, t_cmd *current)
{
	if (!tmp->next && tmp->prev->type == E_SPACE)
		replace_dollar(&tmp->data);
	if (tmp->next && tmp->next->type == E_SPACE && tmp->prev->type == E_SPACE)
		if (tmp->type == E_D_QUOTE)
			replace_dollar(&tmp->data);
	add_to_cmd(tmp->data, current);
}

// void	dollar_cmd_handler(t_lexer *tmp)
// {
	
// 		replace_dollar(&tmp->data);
// }

// void	env_handler(t_lexer *tmp, t_cmd *current)
// {
// 	while (tmp)
// 	{
// 		tmp = tmp->next;
// 	}
		
// }

static void	cmd_adding(t_lexer *tmp, t_cmd *current)
{
	while (tmp)
	{
			// dollar_cmd_handler(tmp)
		if (is_cmd(tmp->type) || is_redirection(tmp->type))
		{
			if (tmp->next && is_quote(tmp->next->type))
			{
				printf("%s\n", tmp->data);
				tmp->data = ft_strjoin(tmp->data, tmp->next->data);
				printf("%s\n", tmp->data);
				if (is_cmd(tmp->type))
					replace_dollar(&tmp->data);
				printf("%s\n", tmp->data);
				add_to_cmd(tmp->data, current);
				tmp = tmp->next;
			}
			else
				add_to_cmd(tmp->data, current);
		}
		else if (tmp->type == E_PIPE)
			new_cmd(&current);
		else if (tmp->type == E_SPACE)
			add_to_cmd(tmp->data, current);
		else if (is_quote(tmp->type))
			new_quote_cmd(tmp, current);
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

t_cmd	*parser(t_lexer **tokens)
{
	t_cmd	*head;
	t_cmd	*current;
	t_lexer	*tmp;

	tmp = *tokens;
	init_cmd(&head, &current);
	// env_handler(tmp, current);
	cmd_adding(tmp, current);
	return (head);
}
