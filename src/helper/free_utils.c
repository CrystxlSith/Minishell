/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:16:55 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/25 16:16:56 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_token(t_lexer *token)
{
	if (token)
	{
		if (token->data)
			free(token->data);
		if (token->data)
			free(token->data);
		free(token);
	}
}

void	free_tokens(t_lexer *tokens)
{
	t_lexer	*current;
	t_lexer	*next;

	if (!tokens)
		return ;
	current = tokens;
	while (current)
	{
		next = current->next;
		free_token(current);
		current = next;
	}
}

void	free_hdc(t_heredoc *head)
{
	t_heredoc	*current;
	t_heredoc	*next;

	current = head;
	while (current)
	{
		next = current->next;
		if (current->break_word)
			free(current->break_word);
		if (current->command)
			free(current->command);
/* 		if (current->redir)
			free_tokens(current->redir); */
		current = next;
	}
}

void	free_parsed_cmd(t_cmd *head)
{
	t_cmd	*current;
	t_cmd	*next;

	if (!head)
		return ;
	current = head;
	while (current)
	{
		next = current->next;
		if (current->str)
			free(current->str);
		if (current->redir)
			free_tokens(current->redir);
		if (current->here_doc)
			free(current->here_doc);
		free_hdc(current->hdc);
		current = next;
	}
}

void	free_minishell(t_env **data)
{
	if ((*data)->var != NULL)
		free_all((*data)->var);
	if ((*data)->pwd != NULL)
		free((*data)->pwd);
	if ((*data)->old_pwd != NULL)
		free((*data)->old_pwd);
}

void	free_all_line(t_lexer *tokens, t_cmd *cmd_parsing, t_env *data)
{
	(void)data;
	if (tokens)
		free_tokens(tokens);
	if (cmd_parsing)
		free_parsed_cmd(cmd_parsing);
}
