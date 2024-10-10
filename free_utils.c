/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:33:26 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/10/10 07:47:58 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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
		free(current);
		current = next;
	}
}

/* void	print_cmd(t_cmd *head)
{
	t_cmd	*current;
	t_lexer	*redir;

	redir = NULL;
	current = head;
	while (current)
	{
		if (current->str)
		{
			printf("Command: ");
			for (int i = 0; current->str[i]; i++)
				printf("%s ", current->str[i]);
		}
		printf("\n");
		printf("Redirections: ");
		redir = current->redir;
		while (redir)
		{
			printf("%s ", redir->data);
			redir = redir->next;
		}
		printf("\n");
		// if (current->index)
			printf("Index: %d\n", current->index);
		// if (current->here_doc)
			printf("Here_doc: %s\n", current->here_doc);
		// if (current->redir_nb)
			printf("Redir_nb: %d\n", current->redir_nb);
		// if (current->elem_nb)
			printf("Elem nb: %d\n", current->elem_nb);
		current = current->next;
	}
} */

/* void	print_tokens(t_lexer *tokens)
{
	t_lexer	*current;

	current = tokens;
	while (current)
	{
		printf("Type: %d\n", current->type);
		printf("Data: %s\n", current->data);
		printf("Index: %d\n", current->index);
		current = current->next;
	}
} */