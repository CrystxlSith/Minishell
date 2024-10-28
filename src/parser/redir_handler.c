/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:10:17 by crycry            #+#    #+#             */
/*   Updated: 2024/10/28 11:14:39 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_redirection(t_cmd *cmd, t_lexer *new_redir)
{
	t_lexer	*last_redir;

	new_redir->next = NULL;
	new_redir->prev = NULL;
	if (!cmd->redir)
		cmd->redir = new_redir;
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

void	handle_redirection(t_lexer **token, t_cmd *cmd)
{
	t_lexer	*new_redir;

	new_redir = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new_redir)
		return ;
	new_redir->type = (*token)->type;
	if ((is_redirection(((*token)->type))) && (*token)->next)
	{
		remove_next_space(token);
		if (is_cmd((*token)->type))
		{
			new_redir->data = ft_strdup((*token)->data);
			if (!new_redir->data)
			{
				free(new_redir);
				return ;
			}
		}
	}
	add_redirection(cmd, new_redir);
}

void	remove_next_space(t_lexer **tmp)
{
	if ((*tmp)->next->next && (*tmp)->next->type == E_SPACE)
	{
		*tmp = (*tmp)->next->next;
	}
}
