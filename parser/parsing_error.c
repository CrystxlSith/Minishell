/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:38:32 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/09/09 15:53:02 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    pipe_error()
{
    while (1)
    {
        
    }
    
}

int	check_synthax_error(t_lexer *tokens)
{
	t_lexer	*tmp;

	tmp = tokens;
	while (tmp->next)
    {
        if (is_redirection(tmp->type))
        {
            if (ft_strchr(IS_TOKEN, tmp->next->data[0]))
            {
                ft_printf("minishell: syntax error near unexpected token `%s'\n", tmp->next->data);
                return (1);
            }
        }
        else if (tmp->type == E_PIPE)
        {
            if (tmp->next->type == E_PIPE)
            {
                ft_printf("minishell: syntax error near unexpected token `||'\n");
                return (1);
            }
        }
        tmp = tmp->next;
    }
	return (0);
}