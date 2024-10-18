/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:33:26 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/10/18 10:43:24 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_token(t_lexer *token)
{
	if (token)
	{
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
		free(current->hdc);
		free(current);
		current = next;
	}
}

void	free_minishell(t_env **data, t_cmd **parsing, t_minishell *minishell)
{
	if (minishell->line_read != NULL)
		free(minishell->line_read);
	if ((*data)->var != NULL)
		free_all((*data)->var);
}

void	free_all_line(t_lexer *tokens, t_cmd *cmd_parsing)
{
	free_tokens(tokens);
	free_parsed_cmd(cmd_parsing);
}
