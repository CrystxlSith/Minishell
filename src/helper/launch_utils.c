/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:18:05 by agiliber          #+#    #+#             */
/*   Updated: 2024/11/04 11:37:31 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_hdc_file(void)
{
	char	*file_name;
	int		i;
	char	*index;

	i = 1;
	file_name = ft_strdup("/tmp/heredoc1.txt");
	while (access(file_name, R_OK) != -1)
	{
		ft_remove(file_name);
		i++;
		index = ft_itoa(i);
		free(file_name);
		file_name = ft_strdup("/tmp/heredoc");
		file_name = ft_strjoin(file_name, index);
		file_name = ft_strjoin(file_name, ".txt");
		free(index);
	}
	free(file_name);
}

void	input_execution(t_env *data, t_cmd *cmd_parsing)
{
	if (detect_hdc(&cmd_parsing) != 0)
	{
		if (cmd_parsing->hdc_count != 0)
			handle_heredoc(&cmd_parsing, &data);
		else
			exec_multiple_cmd(&cmd_parsing, &data);
	}
	else
	{
		if (!cmd_parsing->str && cmd_parsing->redir_nb != 0)
			fork_redirection(&cmd_parsing, &data);
		if (cmd_parsing->str)
			execute_fork(&cmd_parsing, &data);
	}
}

int	execute_commands(t_minishell *minishell, \
t_env **data, t_lexer **tokens, t_cmd **cmd_parsing)
{
	*tokens = tokenize(minishell->line_read);
	*cmd_parsing = parser(tokens, data);
	if (check_cmd_parsing(cmd_parsing, data) == 0)
	{
		if (!ft_strncmp(minishell->line_read, "exit", ft_strlen("exit")))
		{
			if (ft_exit_shell(*cmd_parsing, *data, *tokens) == 0)
				free(minishell->line_read);
		}
		if (!*cmd_parsing)
			return (1);
		input_execution(*data, *cmd_parsing);
	}
	return (0);
}

int	generate_minishell_prompt(t_env *data, t_lexer *tokens, t_cmd *cmd_parsing)
{
	t_minishell	minishell;

	while (1)
	{
		remove_hdc_file();
		init_signals(0);
		minishell.line_read = readline("minishell> ");
		add_history(minishell.line_read);
		if (start_error(minishell.line_read))
		{
			free_parsed_cmd(cmd_parsing);
			// free_all_line(tokens, cmd_parsing);
			rl_on_new_line();
			continue ;
		}
		if (launcher_exec(minishell.line_read, &data) == -1)
			return (free(minishell.line_read), exit(EXIT_FAILURE), -1);
		if (execute_commands(&minishell, &data, &tokens, &cmd_parsing))
			continue ;
		if (minishell.line_read)
			free(minishell.line_read);
		free_all_line(tokens, cmd_parsing);
		rl_on_new_line();
	}
	clear_history();
}
