/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:43:21 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/09/23 15:35:36 by jopfeiff         ###   ########.fr       */
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
		new_tab[i] = data;
		new_tab[i + 1] = NULL;
		free(current->str);
	}
	else
	{
		new_tab = malloc(sizeof(char *) * 2);
		if (!new_tab)
			return ;
		new_tab[0] = data;
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

int	handle_number(char **input, int i)
{
	if ((*input)[i] >= '1' && (*input)[i] <= '9')
		return (1);
	return (0);
}

int	loop_while_dollar(char **input, char **tmp, int i)
{
	int	j;
	
	j = 0;
	while (ft_isdigit((*input)[i]) || ft_isalpha((*input)[i]))
		i++;
	*tmp = malloc(sizeof(char) * i + 1);
	i = 0;
	while (ft_isdigit((*input)[i]) || ft_isalpha((*input)[i]))
	{
		// printf("i = %c\n", (*input)[i]);
		(*tmp)[j] = (*input)[i];
		j++;
		i++;
	}
	(*tmp)[j + 1] = '\0'; // Add null terminator
	// printf("tmp is = %s\n", *tmp);
	return (j);
}

void	init_temp(char **tmp, char **tmp2)
{
	*tmp = NULL;
	*tmp2 = NULL;
}

void	replace_dollar(char **input)
{
	int		i;
	int		j;
	char  *res;
	char	*tmp;
	char	*tmp2;
	char	*env_value;

	env_value = NULL;
	j = 0;
	i = 0;
	// tmp = ft_strdup("");
	// tmp2 = ft_strdup("");
	res = ft_strdup(""); // Initialize res to an empty string
	while ((*input)[j])
	{
		init_temp(&tmp, &tmp2);
		if ((*input)[j] == '$')
		{
			j++;
			if (handle_number(input, j))
			{
				j++;
				continue ;
			}
			j += loop_while_dollar(input, &tmp, j);
			env_value = getenv(tmp);
			if (env_value)
			{
				res = ft_strjoin(res, env_value);
				i += ft_strlen(env_value);
				free(env_value);
			}
		}
		else
		{
			res = ft_realloc(res, ft_strlen(res), ft_strlen(res) + 1);
			res[i] = (*input)[j];
			j++;
			i++;
		}
	}
	res[i] = '\0';
	// free(input);
	*input = res;
	free(tmp);
	free(tmp2);
}

// void	replace_dollar(char **input)
// {
// 	char	*new_input;
// 	int		i = 0, k = 0;

// 	new_input = malloc(sizeof(char) * (ft_strlen(*input) + 1));
// 	if (!new_input)
// 		return ;

// 	while ((*input)[i])
// 	{
// 		if ((*input)[i] == '$')
// 		{
// 			handle_env_var(input, &new_input, &i, &k);
// 			if ((*input)[i] == '\0')
// 				break ;
// 			printf("next_char: %c\n", (*input)[i]);
// 		}
// 		else
// 			new_input[k++] = (*input)[i++];
// 	}
// 	new_input[k] = '\0';
// 	free(*input);
// 	*input = new_input;
// }

// void	handle_env_var(char **input, char **new_input, int *i, int *k)
// {
// 	char	*tmp;
// 	char	*env_value;
// 	int		l = 0;

// 	tmp = malloc(sizeof(char) * (ft_strlen(*input) + 1));
// 	if (!tmp)
// 		return ;
// 	(*i)++;
// 	while ((*input)[*i] && (ft_isalnum((*input)[*i]) || (*input)[*i] == '_'))
// 		tmp[l++] = (*input)[(*i)++];
// 	tmp[l] = '\0';
// 	env_value = getenv(tmp);
// 	free(tmp);
// 	if (env_value)
// 	{
// 		tmp = ft_realloc(*new_input, ft_strlen(*new_input), ft_strlen(*new_input) + ft_strlen(env_value) + 10);
// 		copy_env_value(env_value, new_input, k);
// 	}
// 	else
// 		i += l;
// }

// void	copy_env_value(char *env_value, char **new_input, int *k)
// {
// 	int j = 0;
// 	while (env_value[j])
// 	{
// 		(*new_input)[(*k)++] = env_value[j++];
// 	}
// }

// void	copy_var_name(char **input, char **new_input, int *i, int *k, int l)
// {
// 	int m = 0;
// 	(*new_input)[(*k)++] = '$';
// 	while (m < l)
// 	{
// 		(*new_input)[(*k)++] = (*input)[(*i) - l + m];
// 		m++;
// 	}
// }

void	new_cmd(t_cmd **current)
{
		(*current)->next = create_new_cmd();
		(*current)->next->prev = *current;
		*current = (*current)->next;
}

void	new_quote_cmd(t_lexer *tmp, t_cmd *current)
{
	if (tmp->type == E_D_QUOTE)
		replace_dollar(&tmp->data);
	add_to_cmd(tmp->data, current);
}

static void	cmd_adding(t_lexer *tmp, t_cmd *current)
{
	while (tmp)
	{
		if (is_cmd(tmp->type))
			replace_dollar(&tmp->data);
		if (is_cmd(tmp->type) || is_redirection(tmp->type))
		{
			if (tmp->next && is_quote(tmp->next->type))
			{
				tmp->data = ft_strjoin(tmp->data, tmp->next->data);
				if (tmp->next->type == E_D_QUOTE)
					replace_dollar(&tmp->data);
				add_to_cmd(tmp->data, current);
				if (tmp->next)
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
	// remove_space_token(&head);
	return (head);
}
