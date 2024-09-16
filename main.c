/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:33:26 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/09/16 14:38:28 by agiliber         ###   ########.fr       */
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

void	free_tokens(t_lexer *head)
{
	while (head)
	{
		t_lexer	*tmp;

		tmp = head;
		head = head->next;
		if (tmp->data)
			free(tmp->data);
		free(tmp);
	}
}

void	free_parsed_cmd(t_cmd *head)
{
	t_cmd	*current;
	int	i;

	current = head;
	if (!current)
		return ;
	while (current)
	{
		if (current->str)
		{

			i = 0;
			while (current->str[i])
			{
				free(current->str[i]);
				i++;
			}
			free(current->str);
		}

		current = current->next;
	}
}

int main(int ac, char **av, char **envp)
{
	t_minishell	minishell;
	// Parse les token en separant par pipe
	t_cmd		*cmd_parsing;
	t_lexer		*tokens;
	t_env		*data;

	data = NULL;
	initiate_struc_envp(&data, envp);
	// if (ac || av || envp)
	// 	ft_memset(&minishell ,0 , sizeof(t_minishell));
	tokens = NULL;
	(void)ac;
	(void)av;
	(void)envp;
	while (1)
	{
		// Retourne la ligne entree dans le terminal et ecris un prompt voulu
		minishell.line_read = readline("minishell> ");
		if (minishell.line_read[0] == '\0')
			continue;
		if (!ft_strncmp(minishell.line_read, "exit", ft_strlen("exit")))
			break ;
		// l'historique des commandes effectuees
		add_history(minishell.line_read);
		// Tokenize la commande
		tokens = tokenize(minishell.line_read);
		if (minishell.line_read)
			free(minishell.line_read);
		print_lexers(tokens);
		// parsing of the tokens
		cmd_parsing = parser(&tokens);
		if (!cmd_parsing)
			continue ;
		free_tokens(tokens);
		// print the parsed command
		if (cmd_parsing->str)
			exec_cmd_minishell(&cmd_parsing, &data);
/* 			print_info(cmd_parsing); */
		free_parsed_cmd(cmd_parsing);
		// rl_redisplay();  // Rafraîchit l'affichage du prompt
		rl_on_new_line();
	}
	rl_clear_history();
	return (0);
}
