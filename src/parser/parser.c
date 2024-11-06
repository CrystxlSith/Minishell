/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:44:57 by agiliber          #+#    #+#             */
/*   Updated: 2024/11/06 13:55:21 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_increment(int *i, int *j)
{
	(*i)++;
	(*j)++;
}

void	replace_dollar(char **input, char *res, t_env **data)
{
	t_replace_params	params;

	params.input = input;
	params.res = res;
	params.data = data;
	init_replace_dollar(&params.i, &params.j, &params.res);
	while ((*params.input)[params.j])
	{
		if ((*params.input)[params.j] == '$')
		{
			process_dollar(&params);
		}
		else
		{
			params.res = build_res(params.res, params.i, \
			params.j, params.input);
			free_increment(&params.i, &params.j);
		}
	}
	free(*params.input);
	*params.input = params.res;
}

void	new_cmd(t_cmd **current)
{
	int		i;

	i = (*current)->index + 1;
	(*current)->next = create_new_cmd();
	(*current)->next->prev = *current;
	*current = (*current)->next;
	(*current)->index = i;
	(*current)->hdc = new_hdc_struc(current);
}

static void	cmd_adding(t_lexer *tmp, t_cmd *current)
{
	char	*s_tmp;

	while (tmp)
	{
		s_tmp = ft_strdup(tmp->data);
		if (is_cmd(tmp->type) || is_quote(tmp->type))
		{
			while (tmp->next && (is_quote(tmp->next->type) \
			|| is_cmd(tmp->next->type)))
			{
				s_tmp = ft_strjoin(s_tmp, tmp->next->data);
				tmp = tmp->next;
			}
			add_to_cmd(s_tmp, current, 0);
		}
		else if (tmp->type == E_PIPE)
			new_cmd(&current);
		if (tmp->type == E_REDIR_DEL)
			add_heredoc(&tmp, current);
		else if (is_redirection(tmp->type))
			handle_redirection(&tmp, current);
		current->index++;
		free(s_tmp);
		tmp = tmp->next;
	}
}

t_cmd	*parser(t_lexer **tokens, t_env **data)
{
	char	*res;
	t_cmd	*head;
	t_cmd	*current;
	t_lexer	*tmp;

	res = NULL;
	tmp = *tokens;
	init_cmd(&head, &current);
	initiate_hdc_struc(&head);
	rep_d(tmp, res, data);
	cmd_adding(tmp, current);
	return (head);
}
