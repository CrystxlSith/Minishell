/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:44:42 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/09/25 11:28:34 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redir_handler(t_lexer **token, char **str)
{
	char	*new;

	new = ft_strdup("");
	if (**str == '>')
	{
		if (*(*str + 1) == '>')
		{
			free(new);
			new = ft_strdup(">>");
			create_new_token(E_REDIR_APP, new, token);
			(*str) += 2;
			free(new);
			return ;
		}
		free(new);
		new = ft_strdup(">");
		create_new_token(E_REDIR_OUT, new, token);
		(*str)++;
	}
	else if (**str == '<')
	{
		if (*(*str + 1) == '<')
		{
			free(new);
			new = ft_strdup("<<");
			create_new_token(E_REDIR_DEL, "<<", token);
			(*str) += 2;
			free(new);
			return ;
		}
		free(new);
		new = ft_strdup("<");
		create_new_token(E_REDIR_IN, new, token);
		(*str)++;
	}
	free(new);
}

void	space_handler(t_lexer **tokens, char **str)
{
	char	*new;

	new = malloc(sizeof(char) * 2);
	if (!new)
		return ;
	new[0] = **str;
	new[1] = '\0';
	if (ft_isspace(**str))
	{
		create_new_token(E_SPACE, new, tokens);
		while (**str && ft_isspace(**str))
			(*str)++;
	}
	free(new);
}

void	pipe_handler(t_lexer **tokens, char **str)
{
	char	*new;
	if (*(*str + 1) == '|')
	{
		new = ft_strdup("||");
		create_new_token(E_PIPE, new, tokens);
		(*str) += 2;
		free(new);
		return ;
	}
	new = ft_strdup("|");
	create_new_token(E_PIPE, new, tokens);
	free(new);
	(*str)++;
}
