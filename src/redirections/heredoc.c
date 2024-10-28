/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:35:14 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/25 12:42:43 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	detect_hdc(t_cmd **cmd_parsing)
{
	t_cmd	*tmp;
	int		count;

	count = 0;
	tmp = *cmd_parsing;
	while (tmp)
	{
		if (tmp->hdc_count != 0)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

int	generate_hdc_files(t_cmd **cmd_parsing, int count)
{
	t_cmd	*tmp;
	char	*file_name;
	int		fd;
	int		i;

	i = 1;
	tmp = *cmd_parsing;
	while (tmp && i <= count)
	{
		if (tmp->hdc_count != 0)
		{
			file_name = ft_strdup("/tmp/heredoc");
			file_name = ft_strjoin(file_name, ft_itoa(i));
			file_name = ft_strjoin(file_name, ".txt");
			fd = open(file_name, O_CREAT | O_RDWR | O_APPEND, 0777);
			if (fd == -1)
				return (perror("Failed to open heredoc file"), -1);
			tmp->hdc->file_name = ft_strdup(file_name);
			tmp->hdc->hdc_fd = fd;
			i++;
			free(file_name);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	handle_heredoc(t_cmd **cmd_parsing, t_env **data)
{
	int		count;
	t_cmd	*tmp;
	int		nbr;

	nbr = detect_hdc(cmd_parsing);
	generate_hdc_files(cmd_parsing, nbr);
	count = (*cmd_parsing)->hdc_count;
	tmp = *cmd_parsing;
	if (count == 0)
		return (-1);
	while (nbr > 0 && tmp)
	{
		handle_heredoc_input(tmp, data);
		close(tmp->hdc->hdc_fd);
		tmp = tmp->next;
		nbr--;
	}
	return (0);
}

static int	check_break_word(t_cmd *cmd_parsing, t_minishell *mini, int fd)
{
	int	len;

	len = ft_strlen(cmd_parsing->hdc->break_word);
	if (mini->line_read == NULL
		|| ft_strncmp(cmd_parsing->hdc->break_word, mini->line_read, len) == 0)
	{
		if (cmd_parsing->hdc->next != NULL)
		{
			ft_remove(cmd_parsing->hdc->file_name);
			cmd_parsing->hdc = cmd_parsing->hdc->next;
			cmd_parsing->hdc->hdc_fd = open(cmd_parsing->hdc->prev->file_name, \
				O_CREAT | O_RDWR | O_APPEND, 0777);
			cmd_parsing->hdc->file_name = cmd_parsing->hdc->prev->file_name;
			cmd_parsing->hdc->command = cmd_parsing->hdc->prev->command;
			if (cmd_parsing->hdc->hdc_fd == -1)
			{
				perror("Failed to open heredoc file");
				return (-1);
			}
			return (close(fd), 1);
		}
		else
			return (close(fd), 2);
	}
	return (0);
}

int	handle_heredoc_input(t_cmd *cmd_parsing, t_env **data)
{
	t_minishell	mini;

	while (1)
	{
		init_signals(1);
		mini.line_read = readline("> ");
		if (mini.line_read == NULL)
			return (handle_readline_error(cmd_parsing->hdc->hdc_fd));
		if (launcher_exec(mini.line_read, data) == -1)
			return (free(mini.line_read), exit_failure(cmd_parsing->hdc->hdc_fd));
		if (mini.line_read[0] == '\0' || mini.line_read == NULL)
		{
			free(mini.line_read);
			continue ;
		}
		if (check_break_word(cmd_parsing, &mini, cmd_parsing->hdc->hdc_fd) == 1)
			continue ;
		if (check_break_word(cmd_parsing, &mini, cmd_parsing->hdc->hdc_fd) == 2)
		{
			handle_break_word(cmd_parsing, data);
			break ;
		}
		write_to_heredoc(cmd_parsing->hdc->hdc_fd, mini.line_read);
		free(mini.line_read);
	}
}
