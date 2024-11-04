/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:18:05 by agiliber          #+#    #+#             */
/*   Updated: 2024/11/04 17:56:52 by agiliber         ###   ########.fr       */
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
		init_signals(0);
		minishell.line_read = readline("minishell> ");
		add_history(minishell.line_read);
		if (!minishell.line_read)
		{
			g_sig_status = exit_status(g_sig_status);
			return (-1);
		}
		if (start_error(minishell.line_read, cmd_parsing))
		{
			rl_on_new_line();
			continue ;
		}
		execute_commands(&minishell, &data, &tokens, &cmd_parsing);
		free_all_line(tokens, cmd_parsing);
		free(minishell.line_read);
		rl_on_new_line();
	}
	clear_history();
}
