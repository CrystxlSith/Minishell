/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:44:42 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/09/19 11:55:57 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redir_handler(t_lexer **token, char **str)
{
	if (**str == '>')
	{
		if (*(*str + 1) == '>')
		{
			create_new_token(E_REDIR_APP, ">>", token);
			(*str) += 2;
			return ;
		}
		create_new_token(E_REDIR_OUT, ">", token);
		(*str)++;
	}
	else if (**str == '<')
	{
		if (*(*str + 1) == '<')
		{
			create_new_token(E_REDIR_DEL, "<<", token);
			(*str) += 2;
			return ;
		}
		create_new_token(E_REDIR_IN, "<", token);
		(*str)++;
	}
}

void	space_handler(t_lexer **tokens, char **str)
{
	create_new_token(E_SPACE, " ", tokens);
	(*str)++;
}

void	pipe_handler(t_lexer **tokens, char **str)
{
	if (*(*str + 1) == '|')
	{
		create_new_token(E_PIPE, "||", tokens);
		(*str) += 2;
		return ;
	}
	create_new_token(E_PIPE, "|", tokens);
	(*str)++;
}
