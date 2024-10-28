/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:43:21 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/10/28 15:07:58 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	replace_dollar(char **input, char *res, int i, int j)
{
	char	*tmp;
	char	*tmp2;

	res = ft_strdup("");
	while ((*input)[j])
	{
		init_temp(&tmp, &tmp2);
		if ((*input)[j] == '$')
		{
			if (handle_number(input, &j, tmp, tmp2))
				continue ;
			j += loop_while_dollar(input, &tmp, j, tmp2);
			handle_question(&res, tmp, &i);
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
	int		i;

	i = (*current)->index + 1;
	(*current)->next = create_new_cmd();
	(*current)->next->prev = *current;
	*current = (*current)->next;
	(*current)->index = i;
	(*current)->hdc = new_hdc_struc(current);
}

void	new_quote_cmd(t_lexer *tmp, char *res)
{
	if (tmp->type == E_D_QUOTE)
		replace_dollar(&tmp->data, res, 0, 0);
}

static void	cmd_adding(t_lexer *tmp, t_cmd *current)
{
	char	*s_tmp;

	while (tmp)
	{
		s_tmp = tmp->data;
		if (is_cmd(tmp->type) || is_quote(tmp->type))
		{
			while (tmp->next && (is_quote(tmp->next->type) \
			|| is_cmd(tmp->next->type)))
			{
				s_tmp = ft_strjoin(s_tmp, tmp->next->data);
				tmp = tmp->next;
			}
			add_to_cmd(s_tmp, current);
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

t_cmd	*parser(t_lexer **tokens)
{
	char	*res;
	t_cmd	*head;
	t_cmd	*current;
	t_lexer	*tmp;

	res = NULL;
	tmp = *tokens;
	init_cmd(&head, &current);
	initiate_hdc_struc(&head);
	rep_d(tmp, res);
	cmd_adding(tmp, current);
	return (head);
}
