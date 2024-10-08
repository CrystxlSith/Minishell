/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:33:17 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/10/08 09:59:05 by jopfeiff         ###   ########.fr       */
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
void	add_index_to_token(t_lexer *tokens)
{
	t_lexer	*current;
	int		i;

	current = tokens;
	i = 0;
	while (current != NULL)
	{
		current->index = i;
		current = current->next;
		i++;
	}
}

t_lexer	*remove_space_tokens(t_lexer *head)
{
	t_lexer	*current;
	t_lexer	*next;

	current = head;
	while (current)
	{
		next = current->next;
		if (current->type == E_SPACE)
		{
			if (current->prev)
				current->prev->next = current->next;
			if (current->next)
				current->next->prev = current->prev;
			free(current->data);
			free(current);
		}
		current = next;
	}
	return (head);
}
