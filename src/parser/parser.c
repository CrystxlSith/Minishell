/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:43:21 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/09/26 16:16:34 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	replace_dollar(char **input, char *res, int i, int j)
{
	char	*tmp;
	char	*tmp2;

	while ((*input)[j])
	{
		init_temp(&tmp, &tmp2);
		if ((*input)[j] == '$')
		{
			if (handle_number(input, &j, tmp, tmp2))
				continue ;
			j += loop_while_dollar(input, &tmp, j, tmp2);
			handle_env_value(&res, tmp, &i);
		}
		else
		{
			res = build_res(res, i, j, input);
			free(tmp);
			free(tmp2);
			i++;
			j++;
		}
	}
	free(*input);
	*input = res;
}

void	new_cmd(t_cmd **current)
{
	(*current)->next = create_new_cmd();
	(*current)->next->prev = *current;
	*current = (*current)->next;
}

void	new_quote_cmd(t_lexer *tmp, t_cmd *current, char *res)
{
	if (tmp->type == E_D_QUOTE)
		replace_dollar(&tmp->data, res, 0, 0);
	add_to_cmd(tmp->data, current);
}

static void	cmd_adding(t_lexer *tmp, t_cmd *current, char *res)
{
	while (tmp)
	{
		if (is_cmd(tmp->type))
			replace_dollar(&tmp->data, res, 0, 0);
		if (is_cmd(tmp->type))
		{
			if (tmp->next && is_quote(tmp->next->type))
			{
				tmp->data = ft_strjoin(tmp->data, tmp->next->data);
				replace_dollar(&tmp->data, res, 0, 0);
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
			new_quote_cmd(tmp, current, res);
		if (is_redirection(tmp->type))
			handle_redirection(&tmp, current);
		tmp = tmp->next;
	}
}

t_cmd	*parser(t_lexer **tokens)
{
	char	*res;
	t_cmd	*head;
	t_cmd	*current;
	t_lexer	*tmp;

	res = ft_strdup("");
	tmp = *tokens;
	init_cmd(&head, &current);
	cmd_adding(tmp, current, res);
	return (head);
}
