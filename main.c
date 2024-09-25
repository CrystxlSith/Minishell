/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:33:26 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/09/25 15:11:31 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// ################################  RAF AGT ################################ //
// 1) corriger la fonction CD pour gerer tous les cas de figures			  //
// 2) programmer les bons messages d'erreur									  //
// 3) programmer le builtin exit											  //
// 4) corriger les segfault													  //
// 5) programmer le heredoc													  //
// 6) tenter de casser le code												  //
// ########################################################################## //

void	print_cmd(t_cmd *head)
{
	t_cmd	*current;
	t_lexer	*redir;

	redir = NULL;
	current = head;
	while (current)
	{
		if (current->str)
		{
			printf("Command: ");
			for (int i = 0; current->str[i]; i++)
				printf("%s", current->str[i]);
		}
		printf("\n");
		printf("Redirections: ");
		redir = current->redir;
		while (redir)
		{
			printf("%s ", redir->data);
			redir = redir->next;
		}
		printf("\n");
		// if (current->index)
			printf("Index: %d\n", current->index);
		// if (current->here_doc)
			printf("Here_doc: %s\n", current->here_doc);
		// if (current->redir_nb)
			printf("Redir_nb: %d\n", current->redir_nb);
		// if (current->elem_nb)
			printf("Elem nb: %d\n", current->elem_nb);
		current = current->next;
	}
}

void	print_tokens(t_lexer *head)
{
	t_lexer	*current;

	current = head;
	while (current)
	{
		printf("Token: '%s'\n", current->data);
		printf("Type: %d\n", current->type);
		printf("Index: %d\n", current->index);
		current = current->next;
	}
}

void free_token(t_lexer *token)
{
	if (token)
	{
		free(token->data); // Free the duplicated data
		free(token);           // Free the token itself
	}
}

void free_tokens(t_lexer *tokens)
{
	t_lexer *current; 
	t_lexer *next;

	current = tokens;
	while (current)
	{
		next = current->next;
		free_token(current);
		current = next;
	}
}

void	free_parsed_cmd(t_cmd *head)
{
	t_cmd	*current;
	t_cmd	*next;
	// int		i;

	current = head;
	while (current)
	{
		next = current->next;
		if (current->str)
		{
			// i = 0;
			// while (current->str[i])
			// {
				// free(current->str[i]);
			// 	i++;
			// }
				free(current->str);
		}
		if (current->redir)
			free_tokens(current->redir);
		free(current);
		current = next;
	}
}

int main(int ac, char **av, char **envp)
{
	t_minishell	minishell;
	t_cmd		*cmd_parsing;
	t_lexer		*tokens;
	t_env		*data;


	data = NULL;
	// initiate_struc_envp(&data, envp);
	tokens = NULL;
	(void)ac;
	(void)av;
	(void)envp;
	while (1)
	{
		minishell.line_read = readline("minishell> ");
		if (minishell.line_read[0] == '\0')
			continue ;
		if (!ft_strncmp(minishell.line_read, "exit", ft_strlen("exit")))
		{
			if (minishell.line_read)
				free(minishell.line_read);
			rl_clear_history();	
			break ;
		}
		add_history(minishell.line_read);
		tokens = tokenize(minishell.line_read);
		// print_tokens(tokens);	
		if (lex_error(tokens) || !tokens)
		{
			free_tokens(tokens);
			rl_on_new_line();
			if (minishell.line_read)
				free(minishell.line_read);
			continue ;
		}
		if (minishell.line_read)
			free(minishell.line_read);
		cmd_parsing = parser(&tokens);
		// print_tokens(tokens);
		if (!cmd_parsing)
			continue ;
		// fill_nbr_element(&cmd_parsing);
		// print_cmd(cmd_parsing);
		// if (cmd_parsing->str)
		//  	execute_fork(&cmd_parsing, &data);
		free_parsed_cmd(cmd_parsing);
		free_tokens(tokens);
		// rl_on_new_line();
	}
	rl_clear_history();
	return (0);
}
