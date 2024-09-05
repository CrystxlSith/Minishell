/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 09:16:44 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/09/05 14:43:46 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
// Create a new token

void	init_new_token(t_token *new_token, t_token_type type, char *data)
{
	new_token->next = NULL;
	new_token->data = ft_strdup(data);
	new_token->type = type;
}

//Create new token
void create_new_token(t_token_type  type, char *data, t_token **tokens)
{
	t_token *new_token;
	t_token *last;
	
	if (!data || !tokens)
		return ;
	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return ;
	init_new_token(new_token, type, data);
	if (!*tokens)
	{
		*tokens = new_token;
		new_token->prev = NULL;
	}
	else
	{
		last = find_last(*tokens);
		last->next = new_token;
		new_token->prev = last;
	}
}
