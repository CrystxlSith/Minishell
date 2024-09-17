/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:38:32 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/09/17 09:34:26 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	double_pipe_err(t_lexer *tokens)
{
	if (tokens->next->type == E_PIPE && (!tokens->next->next || !tokens->prev))
		return (1);
	return (0);
}

int	single_pipe_err(t_lexer *tokens)
{
	if (!tokens->prev || !tokens->next)
		return (1);
	return (0);
}

void	first_error(t_lexer *tokens)
{
	while (tokens->next)
	{
		if (tokens->type == E_PIPE)
		{
			if (double_pipe_err(tokens))
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `||'\n", 2);
				return ;
			}
			else if (single_pipe_err(tokens))
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
				return ;
			}
		}
		tokens = tokens->next;
	}
}

int	check_synthax_error(t_lexer *tokens)
{
	t_lexer	*tmp;

	tmp = tokens;
	first_error(tmp);	
	return (0);
}
