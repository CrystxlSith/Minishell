/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycry <crycry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:50:52 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/10/09 13:05:08 by crycry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	add_count_elem(char **data)
{
	int	i;

	i = 0;
	while (data[i])
		i++;
	return (i);
}

void	init_cmd(t_cmd **head, t_cmd **current)
{
	*head = malloc(sizeof(t_cmd));
	*current = *head;
	(*head)->elem_nb = 0;
	(*head)->str = NULL;
	(*head)->redir_nb = 0;
	(*head)->here_doc = NULL;
	(*head)->hdc = NULL;
	(*head)->redir = NULL;
	(*head)->next = NULL;
	(*head)->prev = NULL;
}

t_cmd	*create_new_cmd(void)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->str = NULL;
	new_cmd->redir_nb = 0;
	new_cmd->elem_nb = 0;
	new_cmd->here_doc = NULL;
	new_cmd->hdc = NULL;
	new_cmd->redir = NULL;
	new_cmd->next = NULL;
	new_cmd->prev = NULL;
	return (new_cmd);
}

void	add_heredoc(t_lexer **token, t_cmd *current)
{
	int		i;

	i = 0;
	while (current->str[i])
		i++;
	while (current->next != NULL)
		current = current->next;
	if (current->str != NULL)
	{
		current->hdc->command = (char **)malloc(sizeof(char *) * i + 1);
		if (!current->hdc->command)
			return ;
		i = 0;
		while (current->str[i])
		{
			current->hdc->command[i] = ft_strdup(current->str[i]);
			i++;
		}
	}
	if ((*token)->next->type == E_SPACE)
		(*token) = (*token)->next;
	current->hdc->break_word = ft_strdup((*token)->next->data);
	(*token) = (*token)->next;
}

int	handle_question(char **res, char *tmp, int *i)
{
	char	*tmp2;

	tmp2 = ft_itoa(g_sig_status);
	if (!ft_strncmp(tmp, "?", 1))
	{
		*res = ft_strjoin(*res, tmp2);
		*i += ft_strlen(tmp2);
		free(tmp2);
		return (1);
	}
	free(tmp2);
	handle_env_value(res, tmp, i);
	return (0);
}
