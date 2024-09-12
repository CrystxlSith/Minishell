/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:33:17 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/09/12 11:45:15 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lexer	*find_last(t_lexer *node)
{
	if (!node)
		return (NULL);
	while (node->next)
		node = node->next;
	return (node);
}

//add index to token
void add_index_to_token(t_lexer *tokens)
{
	t_lexer *current;
    int i;

	current = tokens;
    i = 0;
	while (current != NULL)
	{
		current->index = i;
		current = current->next;
		i++;
	}
}
