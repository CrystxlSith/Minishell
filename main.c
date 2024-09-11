/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:33:26 by jopfeiff          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/09/11 07:31:40 by jopfeiff         ###   ########.fr       */
=======
/*   Updated: 2024/09/11 11:52:56 by agiliber         ###   ########.fr       */
>>>>>>> c7eef02ccb44611afe09d1efce124c0469f4b79a
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	free_tokens(t_lexer *head)
{
	t_lexer	*current;

	current = head;
	if (!current)
		return ;
	while (current != NULL)
	{
		head = current->next;
		free(current->data);
		free(current);
		current = head;
	}
}

void	free_parsed_cmd(t_cmd *head)
{
	t_cmd	*current;

	current = head;
	if (!current)
		return ;
	while (current != NULL)
	{
		head = current->next;
		if (current->str)
			ft_free_array(current->str);
		if (current->here_doc)
			free(current->here_doc);
		if (current->redir)
			free_tokens(current->redir);
		free(current);
		current = head;
	}
}


int main(int ac, char **av, char **envp)
{
	t_minishell	minishell;
	// Parse les token en separant par pipe
	t_cmd		*cmd_parsing;
	t_lexer		*tokens;

	// if (argc || argv || env)
	// 	ft_memset(&minishell ,0 , sizeof(t_minishell));
	tokens = malloc(sizeof(t_lexer));
	(void)ac;
	(void)av;
	while (1)
	{
		// Retourne la ligne entree dans le terminal et ecris un prompt voulu
		minishell.line_read = readline("minishell> ");
		if (minishell.line_read[0] == '\0')
			continue;
		// l'historique des commandes effectuees
		add_history(minishell.line_read);
		// Simule une sortie qui inclut un saut de ligne
		printf("Exécution d'une commande...\n");
		// Tokenize la commande
		tokens = tokenize(minishell.line_read);
		print_lexers(tokens);
		// parsing of the tokens
		cmd_parsing = parser(&tokens);
		builtins(cmd_parsing->str, envp);
		// print the parsed command
		if (cmd_parsing->str)
			print_info(cmd_parsing);
		// Indique à readline que nous sommes sur une nouvelle ligne
		if (!ft_strncmp(minishell.line_read, "exit", ft_strlen("exit")))
			break ;
		if (minishell.line_read)
			free(minishell.line_read);
		free_tokens(tokens);
		free_parsed_cmd(cmd_parsing);
		// rl_redisplay();  // Rafraîchit l'affichage du prompt
		rl_on_new_line();
	}
	rl_clear_history();
	return 0;
}
