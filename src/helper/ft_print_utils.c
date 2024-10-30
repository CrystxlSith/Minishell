/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycry <crycry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:13:26 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/30 17:21:02 by crycry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

 void	print_cmd(t_cmd *head)
{
	t_cmd	*current;

	current = head;
	while (current)
	{
		if (current->str)
		{
			printf("Command: ");
			for (int i = 0; current->str[i]; i++)
				printf("%s\n", current->str[i]);
		}
		printf("\n");
		printf("Redirections: ");
		printf("\n");
			printf("Index: %d\n", current->index);
			printf("Here_doc: %s\n", current->here_doc);
			printf("Redir_nb: %d\n", current->redir_nb);
			printf("Elem nb: %d\n", current->elem_nb);
		current = current->next;
	}
}
 
void	print_tokens(t_lexer *tokens)
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
}

void	print_heredoc(t_heredoc *hdc)
{
	t_heredoc	*current;

	current = hdc;
	while (current)
	{
		printf("current->break_word: %s\n", current->break_word);
		printf("current->command[0]: %s\n", current->command[0]);
		current = current->next;
	}
}
