/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:33:17 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/09/05 14:45:25 by jopfeiff         ###   ########.fr       */
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

//add index to token
void add_index_to_token(t_token *tokens)
{
	t_token *current = tokens;
    int i;

    i = 0;
	while (current != NULL)
	{
		current->index = i;
		current = current->next;
		i++;
	}
}