/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:43:21 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/10/08 13:04:53 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_question(char **res, char *tmp, int *i)
{
	char *tmp2;

	tmp2 = ft_itoa(g_sig_status);
	if (!ft_strncmp(tmp, "?", 1))
	{
		*res = ft_strjoin(*res, tmp2);
		*i += ft_strlen(tmp2);
		free(tmp2);
		return (1);
	}
	free(tmp2);
	return (0);
}

void	replace_dollar(char **input, char *res, int i, int j)
{
	char	*tmp;
	char	*tmp2;

	// if (i == -1)
	// {
	// 	free(*input);
	// 	*input = ft_strdup(*input);
	// 	return ;
	// }
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
		s_tmp = ft_strdup(tmp->data);
		if (is_cmd(tmp->type) || is_quote(tmp->type))
		{
			if (tmp->next && (is_quote(tmp->next->type) || is_cmd(tmp->next->type)))
			{
				while (tmp->next && (is_quote(tmp->next->type) || is_cmd(tmp->next->type)))
				{
					s_tmp = ft_strjoin(s_tmp, tmp->next->data);
					tmp = tmp->next;
				}
				add_to_cmd(s_tmp, current);
				if (tmp->next)
					tmp = tmp->next;
			}
			else
				add_to_cmd(tmp->data, current);
		}
		else if (tmp->type == E_PIPE)
			new_cmd(&current);
		if (is_redirection(tmp->type))
			handle_redirection(&tmp, current);
		tmp = tmp->next;
	}
}

void	rep_d(t_lexer *tmp, char *res)
{
	while (tmp)
	{
		if (is_cmd(tmp->type) || tmp->type == E_D_QUOTE)
			replace_dollar(&tmp->data, res, 0, 0);
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
