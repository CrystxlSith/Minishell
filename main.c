/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:05:35 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/18 10:14:31 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	g_sig_status;

int	ft_remove(const char *pathname)
{
	struct stat	path_stat;

	if (lstat(pathname, &path_stat) == -1)
		return (-1);
	else
	{
		if (unlink(pathname) == -1)
			return (-1);
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
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
		init_signals(0);
		minishell.line_read = readline("minishell> ");
		add_history(minishell.line_read);
		if (start_error(minishell.line_read))
			continue ;
		if (launcher_exec(minishell.line_read, &data, &cmd_parsing, &minishell) == -1)
		{
			exit(EXIT_FAILURE);
			return (-1);
		}
		tokens = tokenize(minishell.line_read);
		cmd_parsing = parser(&tokens);
		print_cmd(cmd_parsing);
		if (!ft_strncmp(minishell.line_read, "exit", ft_strlen("exit")))
		{

			if (ft_exit_shell(cmd_parsing, data, tokens) == 0)
				free(minishell.line_read);
			// free_all(data->var);
			// free(data);
			// clear_history();
			// return (NULL);
			// exit(EXIT_FAILURE);
		}
		if (!cmd_parsing)
			continue ;
		// print_cmd(cmd_parsing);
		if (cmd_parsing->str)
		{
			if (cmd_parsing->hdc_count != 0)
				handle_heredoc(&cmd_parsing, &data, &minishell);
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
