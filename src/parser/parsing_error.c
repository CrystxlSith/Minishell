/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:38:32 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/09/16 13:35:49 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	first_last_error(t_lexer *tokens)
// {
// 	t_lexer	*tmp;

// 	tmp = tokens;
// 	if (!tmp)
// 		return (1);
// 	if (tmp->type == E_PIPE)
// 	{
// 		ft_printf("minishell: syntax error near unexpected token `%s'\n", "|");
// 		return (1);
// 	}
// 	if (is_redirection(tmp->type))
// 	{
// 		if (!tmp->next)
// 		{
// 			ft_printf("minishell: syntax error near unexpected token `newline'\n");
// 			return (1);
// 		}
// 	}
// 	return (0);
// }

int	check_synthax_error(t_lexer *tokens)
{
	t_lexer	*tmp;

	tmp = tokens;
	// if (first_last_error(tmp))
	// 	return (1);

	while (tmp && tmp->next)
	{
		printf("tmp->data = %s\n", tmp->data);
		if (tmp->type == E_AMPERSAND)
		{
			ft_printf("minishell: syntax error near unexpected token `%s'\n", "&");
			return (1);
		}
		if (tmp->type == E_PIPE)
		{
			if (tmp->next->type == E_PIPE)
			{
				ft_printf("minishell: syntax error near unexpected token `%s'\n", "||");
				return (1);
			}
			else if (tmp->next->type == E_PIPE || tmp->next->type == E_AMPERSAND)
			{
				ft_printf("minishell: syntax error near unexpected token `%s'\n", "|");
				return (1);
			}
		}
		if (is_redirection(tmp->type))
		{
			if (!tmp->next)
			{
				ft_printf("minishell: syntax error near unexpected token `newline'\n");
				return (1);
			}
			if (is_redirection(tmp->next->type))
			{
				ft_printf("minishell: syntax error near unexpected token `%s'\n", tmp->next->data);
				return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}
