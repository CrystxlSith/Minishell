/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:43:21 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/09/06 14:33:58 by jopfeiff         ###   ########.fr       */
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
// 		ft_printf("Command: ");
// 		for (int i = 0; current->str[i]; i++)
// 			ft_printf("%s ", current->str[i]);
// 		ft_printf("\n");
// 		ft_printf("Redirections: ");
// 		redir = current->redir;
// 		while (redir)
// 		{
// 			ft_printf("%s ", redir->data);
// 			redir = redir->next;
// 		}
// 		ft_printf("\n");
// 		ft_printf("Here_doc: %s\n", current->here_doc);
// 		ft_printf("Redir_nb: %d\n", current->redir_nb);
// 		current = current->next;
// 	}
// }

// t_cmd	*parser(t_lexer **tokens)
// {
// 	t_cmd	*parsed_cmd;
// 	t_lexer	*redir;
// 	t_lexer	*tmp;
// 	int		redir_nb;
	
// 	parsed_cmd = malloc(sizeof(t_cmd));
// 	while (*tokens)
// 	{
// 		if ((*tokens)->type = E_CMD)
// 		{
// 			parsed_cmd->str = ft_split((*tokens)->data, ' ');
// 			*tokens = (*tokens)->next;
// 		}
// 		else if ((*tokens)->type = E_REDIR_IN || (*tokens)->type = E_REDIR_OUT || (*tokens)->type = E_REDIR_APP)
// 		{

// 			redir = malloc(sizeof(t_lexer));
// 			redir->data = ft_strdup((*tokens)->data);
// 			redir->type = (*tokens)->type;
// 			redir->next = NULL;
// 			redir->prev = NULL;
// 			redir_nb = 1;
// 			tmp = *tokens;
// 			*tokens = (*tokens)->next;
// 			while (*tokens && (*tokens)->type == E_REDIR_DEL)
// 			{
// 				redir_nb++;
// 				tmp = *tokens;
// 				*tokens = (*tokens)->next;
// 			}
// 			parsed_cmd->redir_nb = redir_nb;
// 			parsed_cmd->redir = redir;
// 		}
// 		else if ((*tokens)->type = E_PIPE)
// 		{
// 			t_cmd	*new_cmd;

// 			new_cmd = malloc(sizeof(t_cmd));
// 			new_cmd->str = NULL;
// 			new_cmd->redir_nb = 0;
// 			new_cmd->here_doc = NULL;
// 			new_cmd->redir = NULL;
// 			new_cmd->next = NULL;
// 			new_cmd->prev = parsed_cmd;
// 			parsed_cmd->next = new_cmd;
// 			parsed_cmd = new_cmd;
// 			*tokens = (*tokens)->next;
// 		}
// 		else if ((*tokens)->type = E_S_QUOTE || (*tokens)->type = E_D_QUOTE)
// 		{
// 			*tokens = (*tokens)->next;
// 		}
// 		else
// 			*tokens = (*tokens)->next;
// 	}
// 	return (parsed_cmd);
// }	