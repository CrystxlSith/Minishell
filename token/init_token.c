/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 09:16:44 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/09/04 15:18:19 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*find_last(t_token *node)
{
	if (!node)
		return (NULL);
	while (node->next)
		node = node->next;
	return (node);
}

// Create a new token
t_token *create_new_token(t_token_type  type, char *data, t_token **tokens)
{
	t_token *new_token;
	t_token *last;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->next = NULL;
	new_token->data = data;
	new_token->type = type;
	if (!*tokens)
		new_token->prev = NULL;
	else
	{
		last = find_last(*tokens);
		new_token->prev = last;
	}
	return (new_token);
}

// Add a new token to the list
void	new_token(t_token **tokens, t_token *new_node)
{
	t_token *tmp = *tokens;
	if (!*tokens)
		*tokens = new_node;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
		new_node->prev = tmp;
	}
}