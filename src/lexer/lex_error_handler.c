/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_error_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycry <crycry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 07:43:18 by kali              #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/09/26 16:25:04 by jopfeiff         ###   ########.fr       */
=======
/*   Updated: 2024/09/28 14:13:28 by crycry           ###   ########.fr       */
>>>>>>> e230fa8f0608e785cc07771d7c7705d805deaa29
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
<<<<<<< HEAD
			printf("minishell: syntax error near unexpected token `%s'\n", \
				current->next->data);
=======
			print_error(LEX_ERR, current->next->data);
>>>>>>> e230fa8f0608e785cc07771d7c7705d805deaa29
			return (1);
		}
		else if (!current->next)
		{
<<<<<<< HEAD
			printf("minishell: syntax error near unexpected token `newline'\n");
=======
			print_error(LEX_ERR, "newline");
>>>>>>> e230fa8f0608e785cc07771d7c7705d805deaa29
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
<<<<<<< HEAD
		printf("minishell: syntax error near unexpected token `||'\n");
=======
		print_error(LEX_ERR, "||");
>>>>>>> e230fa8f0608e785cc07771d7c7705d805deaa29
		return (1);
	}
	if (current->type == E_PIPE)
	{
		if (!current->prev || !current->next || \
			current->next->type == E_PIPE || current->prev->type == E_PIPE)
		{
<<<<<<< HEAD
			printf("minishell: syntax error near unexpected token `%s'\n"\
			, current->data);
=======
			print_error(LEX_ERR, current->data);
>>>>>>> e230fa8f0608e785cc07771d7c7705d805deaa29
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
<<<<<<< HEAD
		printf("bash: syntax error near unexpected token %s\n"\
		, current->data);
=======
		print_error(LEX_ERR, current->data);
>>>>>>> e230fa8f0608e785cc07771d7c7705d805deaa29
		return (1);
	}
	return (0);
}

int	lex_error(t_lexer *head)
{
	t_lexer	*current;

	current = head;
	if (!head)
		return (1);
	remove_space_tokens(&head);
	if ((!ft_strcmp(";", head->data) || \
		!ft_strcmp("!", head->data)) && !head->next)
		return (1);
	while (current)
	{
		if (current->type == E_PIPE)
		{
			if (pipes_err(current))
				return (1);
		}
		else if (current->type == E_AMPERSAND)
		{
			if (ampersand_err(current))
				return (1);
		}
		else if (is_redirection(current->type))
		{
			if (redir_err(current))
				return (1);
		}
		current = current->next;
	}
	return (0);
}
