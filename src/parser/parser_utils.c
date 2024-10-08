/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 08:42:11 by kali              #+#    #+#             */
/*   Updated: 2024/10/08 14:38:39 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


// Ajouter à la liste de redirections
// Copier les informations de redirection
void	handle_redirection(t_lexer **token, t_cmd *cmd)
{
	t_lexer	*new_redir;
	t_lexer	*last_redir;

	new_redir = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new_redir)
		return ;
	new_redir->type = (*token)->type;
	if (((*token)->type) == E_REDIR_DEL)
		add_heredoc(token, cmd);
	if ((is_redirection(((*token)->type))) && (*token)->next && (is_cmd((*token)->next->type)))
	{
		new_redir->data = ft_strdup((*token)->next->data);
		if (!new_redir->data)
		{
			free(new_redir);
			return ;
		}
		*token = (*token)->next;
	}
	new_redir->next = NULL;
	new_redir->prev = NULL;
	if (!cmd->redir)
	{
		cmd->redir = new_redir;
	}
	else
	{
		last_redir = cmd->redir;
		while (last_redir->next)
			last_redir = last_redir->next;
		last_redir->next = new_redir;
		new_redir->prev = last_redir;
	}
	cmd->redir_nb++;
}


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
