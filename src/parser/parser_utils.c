/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 08:42:11 by kali              #+#    #+#             */
/*   Updated: 2024/10/11 10:58:25 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_redirection(t_lexer_type type)
{
	if (type == E_REDIR_IN || type == E_REDIR_OUT || \
	type == E_REDIR_APP || type == E_REDIR_DEL)
		return (1);
	return (0);
}

int	is_cmd(t_lexer_type type)
{
	if (type == E_CMD || type == E_OPTIONS || \
	type == E_ARG)
		return (1);
	return (0);
}

int	is_quote(t_lexer_type type)
{
	if (type == E_D_QUOTE || type == E_S_QUOTE)
		return (1);
	return (0);
}
