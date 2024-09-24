/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:43:21 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/09/24 16:27:55 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// static void	add_to_cmd2(char *data, t_cmd *current)
// {
// 	char	**new_tab;
// 	int		i;
// 	int		count;

// 	count = 0;
// 	if (current->str)
// 	{
// 		while (current->str[count])
// 			count++;
// 		new_tab = malloc(sizeof(char *) * (count + 2));
// 		if (!new_tab)
// 			return ;
// 		i = 0;
// 		while (i < count)
// 		{
// 			new_tab[i] = current->str[i];
// 			i++;
// 		}
// 		new_tab[i] = data;
// 		new_tab[i + 1] = NULL;
// 		free(current->str);
// 	}
// 	else
// 	{
// 		new_tab = malloc(sizeof(char *) * 2);
// 		if (!new_tab)
// 			return ;
// 		new_tab[0] = data;
// 		new_tab[1] = NULL;
// 	}
// 	current->only_cmd = new_tab;
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
		(*tmp)[j] = (*input)[i];
		j++;
		i++;
	}
	(*tmp)[j] = '\0'; // Add null terminator
	return (j);
}

void	init_temp(char **tmp, char **tmp2)
{
	// if (tmp)
	// 	free(tmp);
	// if (tmp2)
	// 	free(tmp2);
	*tmp = malloc(sizeof(char) * 100);
	if (!*tmp)
		return ;
	*tmp2 = malloc(sizeof(char) * 100);
	if (!*tmp2)
		return ;
	// *res = malloc(sizeof(char) * BUFFER_SIZE);
	// if (!*res)
	// 	return ;
	// (*res)[0] = '\0';
	(*tmp)[0] = '\0';
	(*tmp2)[0] = '\0';
}

void	replace_dollar(char **input)
{
	int		i;
	int		j;
	char	*res;
	char	*tmp;
	char	*tmp2;
	char	*env_value;

	env_value = NULL;
	j = 0;
	i = 0;
	res = ft_strdup("");
	if (!res)
		return;
	init_temp(&tmp, &tmp2);
	while ((*input)[j])
	{
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
				char *new_res = ft_strjoin(res, env_value);
				free(res);
				free(tmp);
				free(tmp2);
				res = new_res;
				i += ft_strlen(env_value);
			}
			else
			{
				free(tmp);
				free(tmp2);
			}
		}
		else
		{
			char *new_res = ft_realloc(res, ft_strlen(res), ft_strlen(res) + 2);
			if (!new_res)
			{
				free(res);
				if (tmp)
					free(tmp);
				if (tmp2)
					free(tmp2);
				return;
			}
			free(res);
			res = new_res;
			res[i] = (*input)[j];
			res[i + 1] = '\0';
			i++;
			j++;
		}
	}
	free(*input);
	*input = ft_strdup(res);
	// if (tmp)
	// 	free(tmp);
	// if (tmp2)
	// 	free(tmp2);
	free(res);
}

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

// void	only_cmd(t_lexer *tmp, t_cmd *current)
// {
// 		while (tmp)
// 	{
// 		if (is_cmd(tmp->type))
// 			replace_dollar(&tmp->data);
// 		if (is_cmd(tmp->type))
// 		{
// 			if (tmp->next && is_quote(tmp->next->type))
// 			{
// 				tmp->data = ft_strjoin(tmp->data, tmp->next->data);
// 				if (tmp->next->type == E_D_QUOTE)
// 					replace_dollar(&tmp->data);
// 				add_to_cmd2(tmp->data, current);
// 				if (tmp->next)
// 					tmp = tmp->next;
// 			}
// 			else
// 				add_to_cmd2(tmp->data, current);
// 		}
// 		else if (tmp->type == E_PIPE)
// 			new_cmd(&current);
// 		else if (tmp->type == E_SPACE)
// 			add_to_cmd2(tmp->data, current);
// 		else if (is_quote(tmp->type))
// 			new_quote_cmd(tmp, current);
// 		if (ft_strchr(IS_TOKEN, tmp->type))
// 			return ;
// 		tmp = tmp->next;
// 	}
// }

char	**only_cmd(char **str)
{
	int		i;
	int		j;
	char	**new_str;
	
	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j] && (!is_redirection(str[i][j]) && str[i][j] != '|'))
		{
			j++;
		}
		if (str[i][j] && (is_redirection(str[i][j]) || str[i][j] == '|'))
		{
			break ;
		}
		i++;
	}
	new_str = malloc(sizeof(char *) * (i + 1));
	if (!new_str)
		return (NULL);
	j = 0;
	while (j < i)
	{
		new_str[j] = ft_strdup(str[j]);
		j++;
	}
	new_str[j] = NULL;
	return (new_str);
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
	current->only_cmd = only_cmd(current->str);
	return (head);
}
