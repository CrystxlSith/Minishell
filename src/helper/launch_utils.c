/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:18:05 by agiliber          #+#    #+#             */
<<<<<<< HEAD
<<<<<<< HEAD
/*   Updated: 2024/10/18 11:23:42 by agiliber         ###   ########.fr       */
=======
/*   Updated: 2024/10/21 10:49:13 by agiliber         ###   ########.fr       */
>>>>>>> Minishell_AGT
=======
/*   Updated: 2024/10/21 13:22:40 by jopfeiff         ###   ########.fr       */
>>>>>>> 0f2fb0de3936a87fb5364b63e3d089244d360d71
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	launcher_exec(char *input, t_env **data, t_cmd **parsing, t_minishell *mini)
{
	if (input == NULL)
	{
		free_minishell(data, parsing, mini);
		clear_history();
		return (-1);
	}
	return (0);
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
		ft_remove("/tmp/heredoc.txt");
	return (0);
}

<<<<<<< HEAD
void	input_execution(t_env *data, t_cmd *cmd_parsing, t_minishell minishell)
{
	if (cmd_parsing->str)
	{
		if (cmd_parsing->hdc_count != 0)
			handle_heredoc(&cmd_parsing, &data, &minishell);
		else
=======
void	input_execution(t_env *data, t_cmd *cmd_parsing, t_minishell *minishell)
{
	if (cmd_parsing->hdc_count != 0)
		handle_heredoc(&cmd_parsing, &data, minishell);
	else
	{
		if (cmd_parsing->str)
>>>>>>> Minishell_AGT
			execute_fork(&cmd_parsing, &data);
	}
}

int	generate_minishell_prompt(t_env *data, t_lexer *tokens, t_cmd *cmd_parsing)
{
	t_minishell	minishell;

	while (1)
	{
		init_signals(0);
		minishell.line_read = readline("minishell> ");
		add_history(minishell.line_read);
		if (start_error(minishell.line_read))
			continue ;
		if (launcher_exec(minishell.line_read, &data, \
			&cmd_parsing, &minishell) == -1)
			return (exit(EXIT_FAILURE), -1);
		tokens = tokenize(minishell.line_read);
		cmd_parsing = parser(&tokens, &data);
		if (!ft_strncmp(minishell.line_read, "exit", ft_strlen("exit")))
		{
			if (ft_exit_shell(cmd_parsing, data, tokens) == 0)
				free(minishell.line_read);
		}
		if (!cmd_parsing)
			continue ;
<<<<<<< HEAD
		input_execution(data, cmd_parsing, minishell);
=======
		input_execution(data, cmd_parsing, &minishell);
>>>>>>> Minishell_AGT
		if (minishell.line_read)
			free(minishell.line_read);
		free_all_line(tokens, cmd_parsing);
		rl_on_new_line();
	}
	clear_history();
}
