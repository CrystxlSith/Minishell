/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 10:01:37 by kali              #+#    #+#             */
/*   Updated: 2024/09/04 15:22:01 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Create a new token
void	print_tokens(t_token *tokens)
{
	t_token *tmp = tokens;
	while (tmp)
	{
		printf("Type: %d, Data: %s\n", tmp->type, tmp->data);
		tmp = tmp->next;
	}
	// while (tmp->prev)
	// {
	// 	printf("Type: %d, Data: %s\n", tmp->type, tmp->data);
	// 	tmp = tmp->prev;
	// }
}

void	quotes_handler(t_token **tokens, char **str)
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
		create_new_token(E_S_QUOTE, ft_strdup(data), tokens);
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
		create_new_token(E_D_QUOTE, ft_strdup(data), tokens);
		(*str)++;
	}
}

// Check if the character is a token and create a new token
static int	check_tokens(char **str, t_token **tokens)
{
	
	if (**str == '|')
		return (create_new_token(E_PIPE, "|", tokens), (*str)++, 1);
	else if (**str == '>')
	{
		if (*(*str + 1) == '>')
			return (create_new_token(E_REDIR_APP, ">>", tokens), (*str) += 2, 1);
		return (create_new_token(E_REDIR_OUT, ">", tokens), (*str)++, 1);
	}
	else if (**str == '<')
	{
		if (*(*str + 1) == '<')
			return (create_new_token(E_REDIR_DEL, "<<", tokens), (*str) += 2, 1);
		return (create_new_token(E_REDIR_IN, "<", tokens), (*str)++, 1);
	}
	else if (**str == '\'' || **str == '"')
		return (quotes_handler(tokens, str), 1);
	return (0);
}

static void	check_cmd(char **str, t_token **tokens)
{
	char	*cmd;
	int	i;

	i = 0;
	cmd = ft_strdup(*str);
	while (**str && !ft_isspace(**str) && !ft_strchr(IS_TOKEN, **str))
	{
		if (ft_strchr(IS_TOKEN, **str))
			break ;
		(*str)++;
		i++;
	}
	cmd[i] = '\0';
	create_new_token(E_CMD, cmd, tokens);
	free(cmd);
}

void	check_options(char **str, t_token **tokens)
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
t_token	*tokenize(char *str)
{
	t_token *tokens = NULL;

	while (*str)
	{
		while (ft_isspace(*str))
			str++;
		if (ft_isalpha(*str))
			check_cmd(&str, &tokens);
		if (ft_strncmp(str, "-", 1) == 0)
			check_options(&str, &tokens);
		if (check_tokens(&str, &tokens))
			continue ;
		else
			str++;
	}
	print_tokens(tokens);
	return (tokens);
}