/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 10:01:37 by kali              #+#    #+#             */
/*   Updated: 2024/09/02 16:38:46 by jopfeiff         ###   ########.fr       */
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
    
}

void	tokenize(char *str)
{
    t_token *tokens = NULL;
	while (*str && ft_isspace(*str) || ft_strchr(SPACE_CHAR, *str))
        str++;
    new_token(*tokens);
}