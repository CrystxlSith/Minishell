/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 09:16:44 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/11/04 16:12:21 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Create a new token
void	init_new_token(t_lexer *new_token, t_lexer_type type, char *data)
{
	new_token->next = NULL;
	new_token->prev = NULL;
	new_token->data = ft_strdup(data);
	if (!new_token->data)
		return ;
	new_token->type = type;
	new_token->index = 0;
}

//Create new token
void	create_new_token(t_lexer_type type, char *data, t_lexer **tokens)
{
	t_lexer	*new_token;
	t_lexer	*last;

	if (!data || !tokens)
		return ;
	new_token = ft_calloc(1, sizeof(t_lexer));
	if (!new_token)
		return ;
	init_new_token(new_token, type, data);
	if (!*tokens)
	{
		*tokens = new_token;
		new_token->prev = NULL;
		new_token->next = NULL;
	}
	else
	{
		last = find_last(*tokens);
		last->next = new_token;
		new_token->prev = last;
	}
}
