/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:38:32 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/09/18 08:23:59 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	double_pipe_err(t_lexer *tokens)
// {
// 	if (tokens->next->type == E_PIPE && (!tokens->next->next || !tokens->prev))
// 		return (1);
// 	return (0);
// }

// int	single_pipe_err(t_lexer *tokens)
// {
// 	if (tokens)
// 		return (1);
// 	return (0);
// }

int	pipe_error(t_lexer *tokens)
{
	if (!tokens->next->next)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	return (0);
}

int	first_error(t_lexer *tokens)
{
	while (tokens->next)
	{
		if (tokens->type == E_PIPE)
		{
			if (pipe_error(tokens))
				return (1);
		}
		tokens = tokens->next;
	}
	return (0);
}

int	check_synthax_error(t_lexer *tokens)
{
	t_lexer	*tmp;

	tmp = tokens;
	if (first_error(tmp))
		return (1);	
	return (0);
}
