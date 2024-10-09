/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_error_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycry <crycry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 07:43:18 by kali              #+#    #+#             */
/*   Updated: 2024/10/09 13:31:12 by crycry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	redir_err(t_lexer *head)
{
	t_lexer	*current;

	current = head;
	if (is_redirection(current->type))
	{
		if (current->next && is_redirection(current->next->type))
		{
			print_error(LEX_ERR, current->next->data);
			return (1);
		}
		else if (!current->next)
		{
			print_error(LEX_ERR, "newline");
			return (1);
		}
	}
	return (0);
}

int	check_quotes(char *str)
{
	int	single_q;
	int	double_q;

	single_q = 0;
	double_q = 0;
	while (*str)
	{
		if (*str == '\'' && double_q == 0)
			single_q = !single_q;
		else if (*str == '"' && single_q == 0)
			double_q = !double_q;
		str++;
	}
	if (single_q % 2 || double_q % 2)
	{
		print_error(LEX_ERR, "quote");
		return (1);
	}
	return (0);
}

int	pipes_err(t_lexer *head)
{
	t_lexer	*current;

	current = head;
	if (!ft_strcmp("||", current->data))
	{
		print_error(LEX_ERR, "||");
		return (1);
	}
	if (current->type == E_PIPE)
	{
		if (!current->prev || !current->next || \
			current->next->type == E_PIPE || current->prev->type == E_PIPE)
		{
			print_error(LEX_ERR, current->data);
			return (1);
		}
	}
	return (0);
}

int	ampersand_err(t_lexer *head)
{
	t_lexer	*current;

	current = head;
	if (current->type == E_AMPERSAND)
	{
		print_error(LEX_ERR, current->data);
		return (1);
	}
	return (0);
}

int	lex_error(char *input)
{
	t_lexer	*current;

	current = tokenize(input);
	if (!current)
		return (1);
	if ((!ft_strcmp(";", current->data) || \
		!ft_strcmp("!", current->data)) && !current->next)
		return (1);
	current = remove_space_tokens(current);
	while (current)
	{
		if ((current->type == E_PIPE && pipes_err(current)) || \
		(current->type == E_AMPERSAND && ampersand_err(current)) || \
		(is_redirection(current->type) && redir_err(current)))
			return (1);
		current = current->next;
	}
	return (0);
}
