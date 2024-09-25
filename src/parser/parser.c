/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:43:21 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/09/25 15:09:10 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	int k;
	int	tmp_len;
	char *new_tmp;
	
	tmp_len = i;
	k = 0;
	j = 0;
	while (ft_isdigit((*input)[i++]) || ft_isalpha((*input)[i]))
		k++;
	new_tmp = malloc(sizeof(char) * (i + 1));
	if (!new_tmp)
		return (0);
	free(*tmp);
	*tmp = new_tmp;
	i = 0;
	while (ft_isdigit((*input)[tmp_len]) || ft_isalpha((*input)[tmp_len]))
	{
		(*tmp)[i] = (*input)[tmp_len];
		i++;
		tmp_len++;
	}
	(*tmp)[i] = '\0';
	return (k);
}

void	init_temp(char **tmp, char **tmp2)
{
	*tmp = malloc(sizeof(char) * 100);
	if (!*tmp)
		return ;
	*tmp2 = malloc(sizeof(char) * 100);
	if (!*tmp2)
		return ;
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
	char	*new_res;
	char	*env_value;

	res = ft_strdup("");
	if (!res)
		return ;
	env_value = NULL;
	j = 0;
	i = 0;
	while ((*input)[j])
	{
		init_temp(&tmp, &tmp2);
		if ((*input)[j] == '$')
		{
			j++;
			if (handle_number(input, j))
			{
				j++;
				free(tmp);
				free(tmp2);
				continue ;
			}
			j += loop_while_dollar(input, &tmp, j);
			j++;
			env_value = getenv(tmp);
			if (env_value)
			{
				new_res = ft_strjoin(res, env_value);
				res = new_res;
				i += ft_strlen(env_value);
			}
			free(tmp);
			free(tmp2);
		}
		else
		{
			new_res = ft_realloc(res, ft_strlen(res), ft_strlen(res) + 2);
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
			if (tmp)
				free(tmp);
			if (tmp2)
				free(tmp2);
			printf("res: %s\n", res);
			i++;
			j++;
		}
	}
	free(*input);
	*input = ft_strdup(res);
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
