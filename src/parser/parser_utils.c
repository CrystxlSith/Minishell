/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 08:42:11 by kali              #+#    #+#             */
/*   Updated: 2024/09/19 12:03:10 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	print_info(t_cmd *parsed_cmd)
// {
// 	t_cmd	*current;
// 	t_lexer	*redir;

// 	current = parsed_cmd;
// 	while (current)
// 	{
// 		if (current->str)
// 		{
// 			ft_printf("Command: ");
// 			for (int i = 0; current->str[i]; i++)
// 				ft_printf("%s ", current->str[i]);
// 			ft_printf("\n");
// 		}
// 		ft_printf("Redirections: ");
// 		redir = current->redir;
// 		while (redir)
// 		{
// 			ft_printf("%s ", redir->data);
// 			redir = redir->next;
// 		}
// 		ft_printf("\n");
// 		ft_printf("Index: %d\n", current->index);
// 		ft_printf("Here_doc: %s\n", current->here_doc);
// 		ft_printf("Redir_nb: %d\n", current->redir_nb);
// 		ft_printf("Elem nb: %d\n", current->elem_nb);
// 		current = current->next;
// 	}
// }

int	add_count_elem(char **data)
{
	int	i;

	i = 0;
	while (data[i])
		i++;
	return (i);
}

void	init_cmd(t_cmd **head, t_cmd **current)
{
	*head = malloc(sizeof(t_cmd));
	*current = *head;
	(*head)->elem_nb = 0;
	(*head)->str = NULL;
	(*head)->redir_nb = 0;
	(*head)->here_doc = NULL;
	(*head)->redir = NULL;
	(*head)->next = NULL;
	(*head)->prev = NULL;
}

t_cmd	*create_new_cmd(void)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->str = NULL;
	new_cmd->redir_nb = 0;
	new_cmd->elem_nb = 0;
	new_cmd->here_doc = NULL;
	new_cmd->redir = NULL;
	new_cmd->next = NULL;
	new_cmd->prev = NULL;
	return (new_cmd);
}

// Ajouter à la liste de redirections
// Copier les informations de redirection
void	handle_redirection(t_lexer *token, t_cmd *cmd)
{
	t_lexer	*new_redir;

	new_redir = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new_redir)
		return ;
	new_redir->type = token->type;
	new_redir->data = strdup(token->data);
	new_redir->next = cmd->redir;
	new_redir->prev = NULL;
	if (cmd->redir)
		cmd->redir->prev = new_redir;
	cmd->redir = new_redir;
	cmd->redir_nb++;
}

int	is_redirection(t_lexer_type type)
{
	if (type == E_REDIR_IN || type == E_REDIR_OUT || \
	type == E_REDIR_APP || type == E_REDIR_DEL)
		return (1);
	return (0);
}
