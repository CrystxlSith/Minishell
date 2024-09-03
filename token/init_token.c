/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 09:16:44 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/09/03 09:18:43 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token *create_new_token(t_token_type  type, char *data)
{
	t_token *new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = type;
	new_token->data = ft_strdup(data);
	new_token->next = NULL;
	return (new_token);	
}

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
	}
}