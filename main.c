/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:33:26 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/09/09 16:07:22 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"


void	free_tokens(t_lexer *head)
{
	t_lexer	*current;

	current = head;
	while (current != NULL)
	{
		head = current->next;
		free(current->data);
		free(current);
		current = head;
	}
}

int main(/*int argc, char const *argv[], char const *env[]*/)
{
	t_minishell	minishell;
	// Parse les token en separant par pipe
	t_cmd		*cmd_parsing;
	t_lexer		*tokens;

	// if (argc || argv || env)
	// 	ft_memset(&minishell ,0 , sizeof(t_minishell));
	tokens = malloc(sizeof(t_lexer));
	while (1)
	{
		// Retourne la ligne entree dans le terminal et ecris un prompt voulu
		minishell.line_read = readline("minishell> ");
		if (minishell.line_read)
		{
			// Permet l'utilisation des fleches pour naviguer dans
			// l'historique des commandes effectuees
			add_history(minishell.line_read);
		}
		// Simule une sortie qui inclut un saut de ligne
		printf("Exécution d'une commande...\n");
		// Tokenize la commande
		tokens = tokenize(minishell.line_read);
		// print_lexers(tokens);
		// parsing of the tokens
		cmd_parsing = parser(&tokens);
		// print the parsed command
		// if (cmd_parsing->str)
		// 	print_info(cmd_parsing);
		// Indique à readline que nous sommes sur une nouvelle ligne
		rl_on_new_line();
		// rl_redisplay();  // Rafraîchit l'affichage du prompt
		if (!ft_strncmp(minishell.line_read, "exit", ft_strlen("exit")))
			break ;
		free(minishell.line_read);
		free_tokens(tokens);
	}
	rl_clear_history();
	return 0;
}
