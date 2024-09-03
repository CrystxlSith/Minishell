/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 10:01:37 by kali              #+#    #+#             */
/*   Updated: 2024/09/03 09:20:41 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_tokens(t_token *tokens)
{
	t_token *tmp = tokens;
	while (tmp)
	{
		printf("Type: %d, Data: %s\n", tmp->type, tmp->data);
		tmp = tmp->next;
	}
}
static void	check_tokens(char **str, t_token **tokens)
{
	if (**str == '|')
		new_token(tokens, create_new_token(E_PIPE, "|"));
	else if (**str == '<')
		new_token(tokens, create_new_token(E_REDIR_IN, "<"));
	else if (**str == '>')
		new_token(tokens, create_new_token(E_REDIR_OUT, ">"));
	else if (**str == ' ')
		new_token(tokens, create_new_token(E_SPACES, " "));
	else if (**str == '\'')
		new_token(tokens, create_new_token(E_S_QUOTE, "'"));
	else if (**str == '"')
		new_token(tokens, create_new_token(E_D_QUOTE, "\""));
	else
		new_token(tokens, create_new_token(E_UNKNOWN, *str));
}

void	tokenize(char *str)
{
	t_token *tokens = NULL;
	int	i;

	i = 0;
	while (*str)
	{
		while (ft_isspace(*str))
			str++;
		check_tokens(&str, &tokens);
		str++;
	}
	print_tokens(tokens);
}