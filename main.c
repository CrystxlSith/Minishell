/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:33:26 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/10/10 15:13:44 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int g_sig_status = 0;

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
				printf("%s\n", current->str[i]);
		}
		printf("\n");
		printf("Redirections: ");
		redir = current->redir;
		// while (redir)
		// {
		// 	printf("%s ", redir->data);
		// 	redir = redir->next;
		// }
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

void free_token(t_lexer *token)
{
	if (token)
	{
		free(token->data);
		free(token);
	}
}

void free_tokens(t_lexer *tokens)
{
	t_lexer	*current;
	t_lexer	*next;

	if (!tokens)
		return ;
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

	if (!head)
		return ;
	current = head;
	while (current)
	{
		next = current->next;
		if (current->str)
			free(current->str);
		if (current->redir)
			free_tokens(current->redir);
		if (current->here_doc)
			free(current->here_doc);
		free(current->hdc);
		free(current);
		current = next;
	}
}

void	print_tokens(t_lexer *tokens)
{
	t_lexer	*current;

	current = tokens;
	while (current)
	{
		printf("Type: %d\n", current->type);
		printf("Data: %s\n", current->data);
		printf("Index: %d\n", current->index);
		current = current->next;
	}
}

int my_remove(const char *pathname)
{
	struct stat path_stat;

	if (lstat(pathname, &path_stat) == -1)
	{
		// Erreur lors de l'obtention des informations
		return -1;
	}
	else
	{
		// C'est un fichier ou un lien symbolique, tenter de le supprimer
		if (unlink(pathname) == -1)
		{
			// Erreur lors de la suppression du fichier
			return -1;
		}
	}
	return 0; // Succès
}

void	free_minishell(t_env **data, t_cmd **parsing, t_minishell *minishell)
{
	if (minishell->line_read != NULL)
		free(minishell->line_read);
	if ((*data)->var != NULL)
		free_all((*data)->var);
/* 	if ((*parsing)->hdc->break_word != NULL)
		free((*parsing)->hdc->break_word);
	if ((*parsing)->hdc->command != NULL)
		free((*parsing)->hdc->command);
	if ((*parsing)->hdc != NULL)
		free((*parsing)->hdc); */
/* 	if (data != NULL)
		free(data); */
}

int	launcher_exec(char *input, t_env **data, t_cmd **parsing, t_minishell *minishell)
{
	if (input == NULL)
	{
		free_minishell(data, parsing, minishell);
		clear_history();
		return (-1);
	}
	if (!ft_strncmp(input, "exit", ft_strlen("exit")))
	{
		free_minishell(data, parsing, minishell);
		clear_history();
		return (-1);
	}
	return (0);
}

void	heredoc_launcher(t_cmd **cmd_parsing, t_env **data, t_minishell *minishell)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == -1)
		exit(0);
	if (pid == 0)
	{
		while (1)
		{
			init_signals(1);
			minishell->line_read = readline("> ");
			if (launcher_exec(minishell->line_read, data, \
				cmd_parsing, minishell) == -1)
			{
				exit(EXIT_FAILURE);
				return ;
			}
			if (minishell->line_read[0] == '\0')
			{
				free(minishell->line_read);
				continue ;
			}
			tokens_hdc = tokenize(minishell->line_read);
			token_input = parser(&tokens_hdc);
			fill_input_hdc(&tokens_hdc, cmd_parsing, data);
		}
	}
	waitpid(pid, &status, 0);
}

int	start_error(char *input)
{
	if (!input)
		exit(EXIT_FAILURE);
	else if (input[0] == '\0')
	{
		free(input);
		return (1);
	}
	else if (lex_error(input))
	{
		free(input);
		return (1);
	}
	if (access("/tmp/heredoc.txt", R_OK) != -1)
		my_remove("/tmp/heredoc.txt");
	return (0);
}

void	free_all_line(t_lexer *tokens, t_cmd *cmd_parsing)
{
	free_tokens(tokens);
	free_parsed_cmd(cmd_parsing);
}

int main(int ac, char **av, char **envp)
{
	t_minishell	minishell;
	t_cmd		*cmd_parsing;
	t_lexer		*tokens;
	t_env		*data;

	data = NULL;
	initiate_struc_envp(&data, envp);
	init_signals(0);
	tokens = NULL;
	(void)ac;
	(void)av;
	while (1)
	{
		minishell.line_read = readline("minishell> ");
		if (start_error(minishell.line_read))
			continue ;
		if (launcher_exec(minishell.line_read, &data, &cmd_parsing, &minishell) == -1)
		{
			exit(EXIT_FAILURE);
			return (-1);
		}
		add_history(minishell.line_read);
		tokens = tokenize(minishell.line_read);
		cmd_parsing = parser(&tokens);
		if (!cmd_parsing)
			continue ;
		if (cmd_parsing->str)
		{
			if (cmd_parsing->hdc->break_word != NULL)
				heredoc_launcher(&cmd_parsing, &data, &minishell);
			else
				execute_fork(&cmd_parsing, &data);
		}
		if (minishell.line_read)
			free(minishell.line_read);
		free_all_line(tokens, cmd_parsing);
		rl_on_new_line();
	}
	clear_history();
	return (0);
}
