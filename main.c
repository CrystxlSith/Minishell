/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:33:26 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/09/18 11:11:17 by kali             ###   ########.fr       */
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
	t_cmd		*cmd_parsing;
	t_lexer		*tokens;
	t_env		*data;


	data = NULL;
	initiate_struc_envp(&data, envp);
	tokens = NULL;
	(void)ac;
	(void)av;
	while (1)
	{
		minishell.line_read = readline("minishell> ");
		if (minishell.line_read[0] == '\0')
			continue ;
		if (!ft_strncmp(minishell.line_read, "exit", ft_strlen("exit")))
			break ;
		add_history(minishell.line_read);
		tokens = tokenize(minishell.line_read);
		if (lex_error(tokens))
			continue ;
		if (minishell.line_read)
			free(minishell.line_read);
		cmd_parsing = parser(&tokens);
		if (!cmd_parsing)
			continue ;
		fill_nbr_element(&cmd_parsing);
		free_tokens(tokens);
		if (cmd_parsing->str)
			execute_fork(&cmd_parsing, &data);
		free_parsed_cmd(cmd_parsing);
		// rl_redisplay();  // Rafraîchit l'affichage du prompt
		rl_on_new_line();
	}
	rl_clear_history();
	return (0);
}
