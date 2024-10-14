/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:50:52 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/10/14 15:09:26 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	(*head)->hdc_count = 0;
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
	new_cmd->hdc_count = 0;
	new_cmd->hdc = NULL;
	new_cmd->redir = NULL;
	new_cmd->next = NULL;
	new_cmd->prev = NULL;
	return (new_cmd);
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
		while (current->str[i])
			i++;
		while (current->next != NULL)
			current = current->next;
		if (current->str != NULL)
		{
			new_hdc->command = (char **)malloc(sizeof(char *) * i);
			if (!new_hdc->command)
				return ;
			i = -1;
			while (current->str[++i])
				new_hdc->command[i] = ft_strdup(current->str[i]);
		}
		if ((*token)->next->type == E_SPACE)
			(*token) = (*token)->next;
		new_hdc->break_word = ft_strdup((*token)->next->data);
		new_heredoc(current, new_hdc);
		(*token) = (*token)->next;
	}
}

void	add_heredoc(t_lexer **token, t_cmd *current)
{
	t_heredoc	*new_hdc;

	new_hdc = malloc(sizeof(t_heredoc));
	if (!new_hdc)
		exit(EXIT_FAILURE);
	fill_heredoc(token, current, new_hdc);
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
