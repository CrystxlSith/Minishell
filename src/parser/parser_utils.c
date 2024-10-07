/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 08:42:11 by kali              #+#    #+#             */
/*   Updated: 2024/10/07 16:44:37 by agiliber         ###   ########.fr       */
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
/* 	char	**cmd; */

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
		//cmd[i] = NULL;
/* 		current->hdc->command = cmd; */
	}
	current->hdc->break_word = ft_strdup((*token)->next->data);
}

// Ajouter à la liste de redirections
// Copier les informations de redirection
void	handle_redirection(t_lexer **token, t_cmd *cmd)
{
	t_lexer	*new_redir;
	t_lexer	*last_redir;

	new_redir = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new_redir)
		return ;
	new_redir->type = (*token)->type;
	if (((*token)->type) == E_REDIR_DEL)
		add_heredoc(token, cmd);
	if ((is_redirection(((*token)->type))) && (*token)->next && (is_cmd((*token)->next->type)))
	{
		new_redir->data = strdup((*token)->next->data);
		*token = (*token)->next;
	}
	new_redir->next = NULL;
	new_redir->prev = NULL;
	if (!cmd->redir)
	{
		cmd->redir = new_redir;
	}
	else
	{
		last_redir = cmd->redir;
		while (last_redir->next)
			last_redir = last_redir->next;
		last_redir->next = new_redir;
		new_redir->prev = last_redir;
	}
	cmd->redir_nb++;
}

int	is_redirection(t_lexer_type type)
{
	if (type == E_REDIR_IN || type == E_REDIR_OUT || \
	type == E_REDIR_APP || type == E_REDIR_DEL)
		return (1);
	return (0);
}

int	is_cmd(t_lexer_type type)
{
	if (type == E_CMD || type == E_OPTIONS || \
	type == E_ARG)
		return (1);
	return (0);
}

int	is_quote(t_lexer_type type)
{
	if (type == E_D_QUOTE || type == E_S_QUOTE)
		return (1);
	return (0);
}
