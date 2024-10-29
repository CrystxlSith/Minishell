/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:33:26 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/10/29 10:35:54 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
			free_all(current->command);
		if (current->file_name)
			free(current->file_name);
		free(current);
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
		if (current->hdc)
			free_hdc(current->hdc);
		free(current);
		current = next;
	}
}

void	free_minishell(t_env *data)
{
	if ((data)->var != NULL)
		free_all((data)->var);
	if ((data)->pwd != NULL)
		free((data)->pwd);
	if ((data)->old_pwd != NULL)
		free((data)->old_pwd);
}

void	free_all_line(t_lexer *tokens, t_cmd *cmd_parsing)
{
	if (cmd_parsing)
		free_parsed_cmd(cmd_parsing);
	if (tokens)
		free_tokens(tokens);
}
