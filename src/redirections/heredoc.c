/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:04:40 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/29 15:01:50 by agiliber         ###   ########.fr       */
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

int	open_hdc_file(char *file_name)
{
	int		fd;

	fd = open(file_name, O_CREAT | O_RDWR | O_APPEND, 0777);
	return (fd);
}

void	generate_hdc_files(t_cmd **cmd_parsing, int count)
{
	t_cmd	*tmp;
	char	*file_name;
	int		i;
	char	*index;

	i = 1;
	tmp = *cmd_parsing;
	while (tmp && i <= count)
	{
		if (tmp->hdc_count != 0)
		{
			index = ft_itoa(i);
			file_name = ft_strdup("/tmp/heredoc");
			file_name = ft_strjoin(file_name, index);
			file_name = ft_strjoin(file_name, ".txt");
			tmp->hdc->hdc_fd = open_hdc_file(file_name);
			if (tmp->hdc->hdc_fd == -1)
				return ;
			tmp->hdc->file_name = ft_strdup(file_name);
			i++;
			free(file_name);
			free(index);
		}
		tmp = tmp->next;
	}
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
	if (ft_strncmp(cmd_parsing->hdc->break_word, mini->line_read, len) == 0)
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
				return (perror("Failed to open heredoc file"), -1);
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
	static int	i;
	int		pid;

	i = 0;
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		while (1)
		{
			init_signals(1);
			mini.line_read = readline("> ");
			i++;
			if (mini.line_read && mini.line_read[0] == '\0')
			{
				write_to_heredoc(cmd_parsing->hdc->hdc_fd, mini.line_read);
				continue ;
			}
			if (check_break_word(cmd_parsing, &mini, cmd_parsing->hdc->hdc_fd) == 1)
			{
				continue ;
				free(mini.line_read);
			}
			else if (check_break_word(cmd_parsing, &mini, cmd_parsing->hdc->hdc_fd) == 2)
			{
				free(mini.line_read);
				handle_break_word(cmd_parsing, data);
				exit(g_sig_status);
			}
			if (mini.line_read)
				write_to_heredoc(cmd_parsing->hdc->hdc_fd, mini.line_read);
			free(mini.line_read);
		}
		if (!mini.line_read)
		{
			print_hdc_error(i, cmd_parsing->hdc->break_word);
			close(cmd_parsing->hdc->hdc_fd);
			exit(1);
		}
	}
	waitpid(pid, &g_sig_status, 0);
	return (0);
}
