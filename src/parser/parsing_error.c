/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:38:32 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/09/11 11:53:16 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	first_last_error(t_lexer *tokens)
{
	t_lexer	*tmp;

	tmp = tokens;
	if (!tmp)
		return (1);
	if (tmp->type == E_PIPE)
	{
		ft_printf("minishell: syntax error near unexpected token `%s'\n", "|");
		return (1);
	}
	if (is_redirection(tmp->type))
	{
		if (!tmp->next)
		{
			ft_printf("minishell: syntax error near unexpected token `%s'\n", "newline");
			return (1);
		}
	}
	while(tmp->next)
		tmp = tmp->next;
	// if (tmp->type == E_PIPE)
	// {
	// 	ft_printf("minishell: syntax error near unexpected token `%s'\n", tmp->data);
	// 	return (1);
	// }
	// if (is_redirection(tmp->type))
	// {
	// 	ft_printf("minishell: syntax error near unexpected token `%s'\n", tmp->prev->data);
	// 	return (1);
	// }
	return (0);
}

int	check_synthax_error(t_lexer *tokens)
{
	t_lexer	*tmp;

	tmp = tokens;
	if (!first_last_error(tmp))
	{
		while (tmp->next)
		{
			// if (is_redirection(tmp->type))
			// {
			// 	if (ft_strchr(IS_TOKEN, tmp->next->data[0]))
			// 	{
			// 		ft_printf("mi: syntax error near unexpected token `%s'\n", tmp->next->data);
			// 		return (1);
			// 	}
			// }
			if (tmp->type == E_PIPE)
			{
				if (ft_strchr(IS_TOKEN, tmp->next->data[0]))
				{
					ft_printf("minishell: syntax error near unexpected token `%s'\n","|");
					return (1);
				}
			}
			tmp = tmp->next;
		}
	}
	return (0);
}