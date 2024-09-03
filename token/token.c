/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 10:01:37 by kali              #+#    #+#             */
/*   Updated: 2024/09/03 12:11:39 by jopfeiff         ###   ########.fr       */
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
}

// Check if the character is a token and create a new token
static int	check_tokens(char **str, t_token **tokens)
{
	
	if (**str == '|')
		return (new_token(tokens, create_new_token(E_PIPE, "|")), (*str)++, 1);
	else if (**str == '>')
	{
		if (*(*str + 1) == '>')
			return (new_token(tokens, create_new_token(E_REDIR_APP, ">>")), (*str)++, 1);
		return (new_token(tokens, create_new_token(E_REDIR_OUT, ">")), 1);
	}
	else if (**str == '<')
	{
		if (*(*str + 1) == '<')
			return (new_token(tokens, create_new_token(E_REDIR_DEL, "<<")), (*str)++, 1);
		return (new_token(tokens, create_new_token(E_REDIR_IN, "<")), 1);
	}
	else if (**str == '>')
		return (new_token(tokens, create_new_token(E_REDIR_OUT, ">")), 1);
	// else if (**str == ' ')
	// 	return (new_token(tokens, create_new_token(E_SPACES, " ")), 1);
	else if (**str == '\'')
		return (new_token(tokens, create_new_token(E_S_QUOTE, "'")), 1);
	else if (**str == '"')
		return (new_token(tokens, create_new_token(E_D_QUOTE, "\"")), 1);
	return (0);
}

static void	check_cmd(char **str, t_token **tokens)
{
	char	*cmd;
	int	i;

	i = 0;
	cmd = *str;
	while (**str && !ft_isspace(**str) && !ft_strchr(IS_TOKEN, **str))
	{
	
		(*str)++;
		i++;
	}
	cmd[i] = '\0';
	new_token(tokens, create_new_token(E_CMD, ft_strdup(cmd)));
	 if (ft_strchr(IS_TOKEN, **str))
	 	check_tokens(str, tokens);
}

// static void	check_arg(char **str, t_token **tokens)
// {
// 	char	*arg;
// 	int	i;

// 	i = 0;
// 	arg = *str;
// 	while (**str && !ft_isspace(**str))
// 	{
// 		(*str)++;
// 		i++;
// 	}
// 	arg[i] = '\0';
// 	if (!check_tokens(str, tokens) && !ft_isspace(**str))
// 		new_token(tokens, create_new_token(E_ARG, ft_strdup(arg)));
// }

// Tokenize the input string
t_token	*tokenize(char *str)
{
	t_token *tokens = NULL;
	int	i;

	i = 0;
	while (*str)
	{
		while (ft_isspace(*str))
			str++;
		check_tokens(&str, &tokens);
		if (ft_isalpha(*str))
			check_cmd(&str, &tokens);
		// if 
		// check_arg(&str, &tokens);
		str++;
	}
	print_tokens(tokens);
	return (tokens);
}