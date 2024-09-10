/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 08:42:11 by kali              #+#    #+#             */
/*   Updated: 2024/09/10 13:33:05 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_info(t_cmd *parsed_cmd)
{
	t_cmd	*current;
	t_lexer	*redir;

	current = parsed_cmd;
	while (current)
	{
		ft_printf("Command: ");
		for (int i = 0; current->str[i]; i++)
			ft_printf("%s ", current->str[i]);
		ft_printf("\n");
		ft_printf("Redirections: ");
		redir = current->redir;
		while (redir)
		{
			ft_printf("%s ", redir->data);
			redir = redir->next;
		}
		ft_printf("\n");
		ft_printf("Index: %d\n", current->index);
		ft_printf("Here_doc: %s\n", current->here_doc);
		ft_printf("Redir_nb: %d\n", current->redir_nb);
		current = current->next;
	}
}


void	init_cmd(t_cmd **head, t_cmd **current)
{
	*head = malloc(sizeof(t_cmd));
	*current = *head;
	(*head)->str = NULL;
	(*head)->redir_nb = 0;
	(*head)->here_doc = NULL;
	(*head)->redir = NULL;
	(*head)->next = NULL;
	(*head)->prev = NULL;
}

t_cmd *create_new_cmd()
{
    t_cmd *new_cmd;

    new_cmd = malloc(sizeof(t_cmd));
    if (!new_cmd)
        return NULL;
    
    // Initialize the command structure
    new_cmd->str = NULL;          // Arguments for execve
    new_cmd->redir_nb = 0;        // No redirection by default
    new_cmd->here_doc = NULL;     // No here document by default
    new_cmd->redir = NULL;        // No redirection tokens by default
    new_cmd->next = NULL;         // No next command by default
    new_cmd->prev = NULL;         // No previous command by default
    return (new_cmd);
}

void	handle_redirection(t_lexer *token, t_cmd *cmd)
{
   t_lexer *new_redir = (t_lexer *)malloc(sizeof(t_lexer));
    if (!new_redir)
        return; // Erreur d'allocation
    // Copier les informations de redirection
    new_redir->type = token->type;
    new_redir->data = strdup(token->data);
    new_redir->next = cmd->redir;
    new_redir->prev = NULL;
    // Ajouter à la liste de redirections
    if (cmd->redir)
        cmd->redir->prev = new_redir;
    cmd->redir = new_redir;
    cmd->redir_nb++;	
}

int	is_redirection(t_lexer_type type)
{
	if (type == E_REDIR_IN || type == E_REDIR_OUT || type == E_REDIR_APP || type == E_REDIR_DEL)
		return (1);
	return (0);
}
