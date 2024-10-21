/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:33:26 by jopfeiff          #+#    #+#             */
<<<<<<< HEAD
<<<<<<< HEAD
/*   Updated: 2024/10/18 10:43:24 by agiliber         ###   ########.fr       */
=======
/*   Updated: 2024/10/18 15:41:57 by agiliber         ###   ########.fr       */
>>>>>>> Minishell_AGT
=======
/*   Updated: 2024/10/18 17:11:34 by jopfeiff         ###   ########.fr       */
>>>>>>> 0f2fb0de3936a87fb5364b63e3d089244d360d71
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_token(t_lexer *token)
{
	if (token)
	{
<<<<<<< HEAD
<<<<<<< HEAD
		free(token->data);
=======
		if (token->data)
			free(token->data);
>>>>>>> Minishell_AGT
=======
		if (token->data)
			free(token->data);
>>>>>>> 0f2fb0de3936a87fb5364b63e3d089244d360d71
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

<<<<<<< HEAD
=======
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

>>>>>>> Minishell_AGT
void	free_parsed_cmd(t_cmd *head)
{
	t_cmd	*current;
	t_cmd	*next;

	if (!head)
		return ;
	current = head;
<<<<<<< HEAD
=======

>>>>>>> Minishell_AGT
	while (current)
	{
		next = current->next;
		if (current->str)
			free(current->str);
		if (current->redir)
			free_tokens(current->redir);
		if (current->here_doc)
			free(current->here_doc);
<<<<<<< HEAD
=======
		free_hdc(current->hdc);
>>>>>>> Minishell_AGT
		free(current->hdc);
		free(current);
		current = next;
	}
}

void	free_minishell(t_env **data, t_cmd **parsing, t_minishell *minishell)
{
<<<<<<< HEAD
	if (minishell->line_read != NULL)
		free(minishell->line_read);
=======
>>>>>>> Minishell_AGT
	if ((*data)->var != NULL)
		free_all((*data)->var);
}

void	free_all_line(t_lexer *tokens, t_cmd *cmd_parsing)
{
<<<<<<< HEAD
	free_tokens(tokens);
	free_parsed_cmd(cmd_parsing);
=======
	if (tokens)
		free_tokens(tokens);
	if (cmd_parsing)
		free_parsed_cmd(cmd_parsing);
>>>>>>> Minishell_AGT
}
