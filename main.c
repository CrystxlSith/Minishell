/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:33:26 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/10/07 16:53:52 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_minishell	minishell;


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
				printf("%s ", current->str[i]);
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
				free(current->str);
		if (current->redir)
			free_tokens(current->redir);
		if (current->here_doc)
			free(current->here_doc);
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

void	free_minishell(t_env **data, t_cmd **parsing)
{
	free(minishell.line_read);
	free_all((*data)->var);
	free((*parsing)->hdc->break_word);
	free((*parsing)->hdc->command);
	free((*parsing)->hdc);
	free(data);
}

int	launcher_exec(char *input, t_env **data, t_cmd **parsing)
{
	if (input == NULL)
	{
		free_minishell(data, parsing);
		clear_history();
		return (-1);
	}
	if (!ft_strncmp(input, "exit", ft_strlen("exit")))
	{
		free_minishell(data, parsing);
		clear_history();
		return (-1);
	}
	return (0);
}

void	heredoc_launcher(t_cmd **cmd_parsing, t_env **data)
{
	t_lexer	*tokens_hdc;
	t_cmd	*token_input;
	int		pid;
	int		status;

	tokens_hdc = NULL;
	token_input = NULL;
	pid = fork();
	if (pid == -1)
		exit(0);
	if (pid == 0)
	{
		while (1)
		{
			minishell.line_read = readline("> ");
			if (launcher_exec(minishell.line_read, data, cmd_parsing) == -1)
			{
				exit(EXIT_FAILURE);
				return ;
			}
			if (minishell.line_read[0] == '\0')
			{
				free(minishell.line_read);
				continue ;
			}
			tokens_hdc = tokenize(minishell.line_read);
			token_input = parser(&tokens_hdc);
			fill_input_hdc(&tokens_hdc, cmd_parsing, data);
		}
	}
	waitpid(pid, &status, 0);
}

int main(int ac, char **av, char **envp)
{
	t_cmd		*cmd_parsing;
	t_lexer		*tokens;
	t_env		*data;

	data = NULL;
	initiate_struc_envp(&data, envp);
	// init_signals();
	tokens = NULL;
	(void)ac;
	(void)av;
	while (1)
	{
		if (access("/tmp/heredoc.txt", R_OK) != -1)
			my_remove("/tmp/heredoc.txt");
		minishell.line_read = readline("minishell> ");
		if (launcher_exec(minishell.line_read, &data, &cmd_parsing) == -1)
		{
			exit(EXIT_FAILURE);
			return (-1);
		}
		if (minishell.line_read[0] == '\0')
		{
			free(minishell.line_read);
			continue ;
		}
		add_history(minishell.line_read);
		tokens = tokenize(minishell.line_read);
		if (lex_error(tokens))
			continue ;
		cmd_parsing = parser(&tokens);
		if (!cmd_parsing)
			continue ;
		if (cmd_parsing->str)
		{
			if (cmd_parsing->hdc->break_word != NULL)
				heredoc_launcher(&cmd_parsing, &data);
			else
				execute_fork(&cmd_parsing, &data);
		}
		if (minishell.line_read)
			free(minishell.line_read);
		free_tokens(tokens);
		free_parsed_cmd(cmd_parsing);
		rl_on_new_line();
	}
	clear_history();
	return (0);
}
