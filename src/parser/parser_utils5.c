/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycry <crycry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:45:44 by agiliber          #+#    #+#             */
/*   Updated: 2024/11/06 20:35:06 by crycry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	process_dollar(t_replace_params *params, t_env **data)
{
	char	*tmp;
	char	*tmp2;

	(void)data;
	init_temp(&tmp, &tmp2);
	if (!(*params->input)[params->j + 1])
	{
		params->j++;
		free(params->res);
		params->res = ft_strdup("$");
		free(tmp);
		free(tmp2);
		return ;
	}
	else if (handle_question(params, data))
	{
		free(tmp);
		free(tmp2);
		return ;
	}
	else if (handle_number(params->input, &params->j, tmp, tmp2))
		return ;
	params->j += loop_while_dollar(params->input, &tmp, params->j, tmp2);
	handle_env_value(&params->res, tmp, &params->i, params->data);
	free(tmp);
}

void	new_heredoc(t_cmd *cmd, t_heredoc *new_hdc)
{
	t_heredoc	*last_hdc;

	new_hdc->next = NULL;
	new_hdc->prev = NULL;
	if (cmd->hdc_count == 0)
		cmd->hdc = new_hdc;
	else
	{
		last_hdc = cmd->hdc;
		while (last_hdc->next)
			last_hdc = last_hdc->next;
		last_hdc->next = new_hdc;
		new_hdc->prev = last_hdc;
	}
	cmd->hdc_count++;
}

void	fill_heredoc(t_lexer **token, t_cmd *current, t_heredoc *new_hdc)
{
	int	i;

	i = 0;
	if ((*token)->type == E_REDIR_DEL && (*token)->next)
	{
		while (current->str != NULL && current->str[i])
			i++;
		while (current->next != NULL)
			current = current->next;
		if (current->str != NULL)
		{
			new_hdc->command = ft_calloc((i + 1), sizeof(char *));
			if (!new_hdc->command)
				return ;
			i = -1;
			while (current->str[++i])
				new_hdc->command[i] = ft_strdup(current->str[i]);
		}
		if ((*token)->next->type == E_SPACE)
			(*token) = (*token)->next;
		new_hdc->break_word = ft_strdup((*token)->next->data);
		(*token) = (*token)->next;
	}
	new_heredoc(current, new_hdc);
}

void	add_heredoc(t_lexer **token, t_cmd *current)
{
	t_heredoc	*new_hdc;

	if (current->hdc_count != 0)
	{
		new_hdc = new_hdc_struc(&current);
		if (!new_hdc)
			exit(EXIT_FAILURE);
		fill_heredoc(token, current, new_hdc);
	}
	else
		fill_heredoc(token, current, current->hdc);
}

void	init_replace_dollar(int *i, int *j, char **res)
{
	*i = 0;
	*j = 0;
	*res = ft_strdup("");
}
