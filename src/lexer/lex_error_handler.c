/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_error_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 07:43:18 by kali              #+#    #+#             */
/*   Updated: 2024/09/24 15:10:12 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lexer	*remove_spaces(t_lexer *head)
{
	t_lexer	*current;
	t_lexer	*new_head;
	t_lexer	*new_current;

	current = head;
	new_head = NULL;
	new_current = NULL;
	while (current)
	{
		if (current->type != E_SPACE)
		{
			if (!new_head)
			{
				new_head = calloc(1, sizeof(t_lexer));
				new_current = new_head;
			}
			else
			{
				new_current->next = malloc(sizeof(t_lexer) * 1);
				new_current = new_current->next;
			}
			new_current->data = current->data;
			new_current->type = current->type;
		}
		current = current->next;
	}
	new_current->next = NULL;
	return (new_head);
}

static int	redir_err(t_lexer *head)
{
	t_lexer	*current;

	current = head;
	while (current)
	{
		if (is_redirection(current->type))
		{
			if (current->next && is_redirection(current->next->type))
			{
				printf("minishell: syntax error near unexpected token `%s'\n", \
				current->next->data);
				// free_tokens(current);
				return (1);
			}
			else if (!current->next)
			{
				printf("minishell: syntax error near unexpected token `newline'\n");
				return (1);
			}
		}
		current = current->next;
	}
	return (0);
}

int	pipes_err(t_lexer *head)
{
	t_lexer	*current;

	current = head;
	while (current)
	{
		if (!ft_strcmp("||", current->data))
		{
			printf("minishell: syntax error near unexpected token ||\n");
			return (1);
		}
		if (current->type && current->type == E_PIPE)
		{
			if (!current->prev || !current->next || \
				(current->next && current->next->type == E_PIPE) || \
				(current->prev && current->prev->type == E_PIPE))
			{
				printf("minishell: syntax error near unexpected token %s\n"\
				, current->data);
				return (1);
			}
		}
		current = current->next;
	}
	return (0);
}

int	ampersand_err(t_lexer *head)
{
	t_lexer	*current;

	current = head;
	while (current)
	{
		if (current->type == E_AMPERSAND)
		{
			printf("bash: syntax error near unexpected token %s\n"\
			, current->data);
			return (1);
		}
		current = current->next;
	}
	return (0);
}

int	lex_error(t_lexer *head)
{
	t_lexer	*current;

	current = head;
	if ((!ft_strcmp(";", head->data) || \
		!ft_strcmp("!", head->data)) && !head->next)
		return (/*free(current),*/ 1);
	if (!ft_strcmp("<<", head->data))
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (/*free(current),*/ 1);
	}
	if (pipes_err(current) || redir_err(current) || ampersand_err(current))
		return (/*free(current),*/ 1);
	return (/*free(current),*/ 0);
}
