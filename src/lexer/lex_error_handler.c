/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_error_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 07:43:18 by kali              #+#    #+#             */
/*   Updated: 2024/09/19 10:28:34 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int  redir_err(t_lexer *head)
{
	t_lexer *current;

	current = head;
	while (current)
	{
		if (is_redirection(current->type))
		{
			if (current->next && is_redirection(current->next->type))	
			{
				printf("minishell: syntax error near unexpected token `%s'\n", current->next->data);
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
		if (current->type == E_PIPE)
		{
			if (!current->prev || !current->next || \
				current->next->type == E_PIPE || current->prev->type == E_PIPE)
			{
				printf("minishell: syntax error near unexpected token %s\n", current->data);
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
			printf("bash: syntax error near unexpected token %s\n", current->data);
			return(1);
		}
		current = current->next;
	}
	return (0);
}

int lex_error(t_lexer *head)
{
	if ((!ft_strcmp(";", head->data) || !ft_strcmp("!", head->data)) && !head->next)
		return (1);
	if (!ft_strcmp("<<", head->data))
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	if (pipes_err(head) || redir_err(head) || ampersand_err(head))
		return (1);
	return (0);
}
