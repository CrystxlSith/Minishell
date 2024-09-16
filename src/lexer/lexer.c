/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:01:08 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/09/16 13:08:22 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Create a new token

void	print_lexers(t_lexer *head)
{
	t_lexer	*current;

	current = head;
	if (!current)
		return ;
	while (current != NULL)
	{
		if (current->data)
			ft_printf("data = %s Type = %d -> index = %d", current->data, current->type, current->index);
		current = current->next;
	}
	ft_printf("NULL\n");
}

//Handle Single && Double quotes
void	quotes_handler(t_lexer **tokens, char **str)
{
	char	quote;

	quote = **str;
	if (quote == '\'')
	{
		char	*data;
		int	i;

		i = 0;
		(*str)++;
		data = *str;
		while (**str && **str != quote)
		{
			(*str)++;
			i++;
		}
		data[i] = '\0';
		create_new_token(E_S_QUOTE, data, tokens);
		(*str)++;
	}
	else if (quote == '"')
	{
		char	*data;
		int	i;

		i = 0;
		(*str)++;
		data = *str;
		while (**str && **str != quote)
		{
			(*str)++;
			i++;
		}
		data[i] = '\0';
		create_new_token(E_D_QUOTE, data, tokens);
		(*str)++;
	}
}

// Check if the character is a token and create a new token
static int	check_tokens(char **str, t_lexer **tokens)
{
	char	unknown[2];

	if (**str == '|')
		return (pipe_handler(tokens, str), 1);
	else if (**str == ' ')
		return (space_handler(tokens, str), 1);
	else if (ft_strchr(IS_REDIRECTION, **str))
		return (redir_handler(tokens, str), 1);
	else if (**str == '\'' || **str == '"')
		return (quotes_handler(tokens, str), 1);
	else if (**str == '&')
	{
		if (*(*str + 1) == '&')
			return (create_new_token(E_AMPERSAND, "&&", tokens), (*str) += 2, 1);
		else
			return (create_new_token(E_AMPERSAND, "&", tokens), (*str)++, 1);
	}
	else if (!strchr(IS_TOKEN, **str) && !ft_isspace(**str))
	{
		unknown[0] = **str;
		unknown[1] = '\0';
		return (create_new_token(E_UNKNOWN, unknown, tokens), (*str)++, 1);
	}
	return (0);
}

static void	check_cmd(char **str, t_lexer **tokens)
{
	char	*cmd;
	int	i;

	i = 0;
	cmd = ft_strdup(*str);
	while (**str && !ft_isspace(**str) && !ft_strchr(IS_TOKEN, **str))
	{
		(*str)++;
		i++;
	}
	cmd[i] = '\0';
	create_new_token(E_CMD, cmd, tokens);
	free(cmd);
}

void	check_options(char **str, t_lexer **tokens)
{
	char	*options;
	int	i;

	i = 0;
	options = ft_strdup(*str);
	while (**str && !ft_isspace(**str) && !ft_strchr(IS_TOKEN, **str))
	{
		if (ft_strchr(IS_TOKEN, **str))
			break ;
		(*str)++;
		i++;
	}
	options[i] = '\0';
	create_new_token(E_OPTIONS, options, tokens);
	free(options);
}

// Tokenize the input string
t_lexer	*tokenize(char *str)
{
	t_lexer *tokens;
	
	tokens = NULL;
	while (*str)
	{
		while (ft_isspace(*str))
			str++;
		if (!*str)
			break ;
		if (*str && ft_isascii(*str) && !ft_strchr(IS_TOKEN, *str) && *str != '-')
			check_cmd(&str, &tokens);
		else if (*str && *str == '-')
			check_options(&str, &tokens);
		else if (*str && check_tokens(&str, &tokens))
			continue ;
		else 
			str++;
	}
	// check_quotes(tokens);
	add_index_to_token(tokens);
	return (tokens);
}
