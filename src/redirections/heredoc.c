/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:04:40 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/23 15:08:07 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_heredoc(t_cmd **cmd_parsing, t_env **data)
{
	int			count;
	t_cmd		*tmp;

	count = (*cmd_parsing)->hdc_count;
	tmp = *cmd_parsing;
	if (count == 0)
		return (-1);
	while (count > 0 && tmp != NULL)
	{
		heredoc(tmp, data);
		count--;
	}
	return (0);
}

static int	check_break_word(t_cmd *cmd_parsing, t_minishell *mini, int fd)
{
	int	len;

	len = ft_strlen(cmd_parsing->hdc->break_word);
	if (ft_strncmp(cmd_parsing->hdc->break_word, mini->line_read, len) == 0)
	{
		if (cmd_parsing->hdc->next != NULL)
		{
			ft_remove("/tmp/heredoc.txt");
			cmd_parsing->hdc = cmd_parsing->hdc->next;
			close(fd);
			return (1);
		}
		else
		{
			close(fd);
			return (2);
		}
	}
	return (0);
}

static int	handle_heredoc_input(t_cmd *cmd_parsing, t_env **data, int fd)
{
	t_minishell	mini;

	while (1)
	{
		init_signals(1);
		mini.line_read = readline("> ");
		if (mini.line_read == NULL)
			return (handle_readline_error(fd));
		if (launcher_exec(mini.line_read, data, &cmd_parsing, &mini) == -1)
			return (free(mini.line_read), exit_failure(fd));
		if (mini.line_read[0] == '\0' || mini.line_read == NULL)
		{
			free(mini.line_read);
			continue ;
		}
		if (check_break_word(cmd_parsing, &mini, fd) == 1)
			break ;
		else if (check_break_word(cmd_parsing, &mini, fd) == 2)
		{
			if (cmd_parsing->prev == NULL && cmd_parsing->next == NULL)
				handle_break_word(cmd_parsing, data);
			break ;
		}
		write_to_heredoc(fd, mini.line_read);
		free(mini.line_read);
	}
	return (0);
}

void	heredoc(t_cmd *cmd_parsing, t_env **data)
{
	int	fd;

	fd = open_heredoc_file(O_CREAT | O_RDWR | O_APPEND);
	if (fd == -1)
	{
		perror("Failed to open heredoc file");
		return ;
	}
	handle_heredoc_input(cmd_parsing, data, fd);
	close(fd);
}
