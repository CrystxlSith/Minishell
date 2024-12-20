/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:41:04 by agiliber          #+#    #+#             */
/*   Updated: 2024/11/04 12:03:35 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_token(t_lexer *token)
{
	if (token)
	{
		if (token->data)
			free(token->data);
		free(token);
	}
}

void	free_tokens(t_lexer *tokens)
{
	t_lexer	*current;
	t_lexer	*next;

	if (!tokens)
		return ;
	current = tokens;
	while (current)
	{
		next = current->next;
		free_token(current);
		current = next;
	}
}
