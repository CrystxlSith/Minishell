/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:43:21 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/10/18 18:06:55 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_increment(char **tmp, char **tmp2, int *i, int *j)
{
	free(*tmp);
	free(*tmp2);
	(*i)++;
	(*j)++;
}

void	replace_dollar(char **input, char *res, t_env **data)
{
	int		i;
	int		j;
	char	*tmp;
	char	*tmp2;

	init_replace_dollar(&i, &j, &res);
	while ((*input)[j])
	{
		init_temp(&tmp, &tmp2);
		if ((*input)[j] == '$')
		{
			if (handle_number(input, &j, tmp, tmp2))
				continue ;
			j += loop_while_dollar(input, &tmp, j, tmp2);
			handle_question(&res, tmp, &i, data);
		}
		else
		{
			res = build_res(res, i, j, input);
			free_increment(&tmp, &tmp2, &i, &j);
		}
	}
	free(*input);
	*input = res;
}

void	new_cmd(t_cmd **current)
{
	int		i;

	i = (*current)->index + 1;
	(*current)->next = create_new_cmd();
	(*current)->next->prev = *current;
	*current = (*current)->next;
	(*current)->index = i;
}

static void	cmd_adding(t_lexer *tmp, t_cmd *current, t_env **data)
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
			add_to_cmd(s_tmp, current);
			free(s_tmp);
		}
		else if (tmp->type == E_PIPE)
			new_cmd(&current);
		if (tmp->type == E_REDIR_DEL)
			add_heredoc(&tmp, current);
		else if (is_redirection(tmp->type))
			handle_redirection(&tmp, current);
		current->index++;
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
	cmd_adding(tmp, current, data);
	return (head);
}
