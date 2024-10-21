/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:04:40 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/21 15:11:52 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_heredoc(t_cmd **cmd_parsing, t_env **data, t_minishell *mini)
{
	int			count;
	t_cmd		*tmp;

	count = (*cmd_parsing)->hdc_count;
	tmp = *cmd_parsing;
	if (count == 0)
		return ;
	while (count > 0 && tmp != NULL)
	{
		heredoc(tmp, data, mini);
		count--;
	}
}

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

static int	check_break_word(t_cmd *cmd_parsing, t_minishell *mini, int fd)
{
	int	len;

	len = ft_strlen(cmd_parsing->hdc->break_word);
	if (mini->line_read == NULL || ft_strncmp(cmd_parsing->hdc->break_word, mini->line_read, len) == 0)
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

static void	handle_heredoc_input(t_cmd *cmd_parsing, t_env **data, \
	t_minishell *mini, int fd)
{
	static int i ;
	
	i = 0;
	while (1)
	{
		init_signals(1);
		mini->line_read = readline("> ");
		i++;
		if (check_break_word(cmd_parsing, mini, fd) == 1)
			break ;
		else if (check_break_word(cmd_parsing, mini, fd) == 2)
		{
			exec_multiple_cmd(&cmd_parsing, data);
			break ;
		}
		if (mini->line_read[0] == '\0')
		{
			write_to_heredoc(fd, mini->line_read);
			continue ;
		}
		if (mini->line_read)
			write_to_heredoc(fd, mini->line_read);
	}
	if (!mini->line_read)
		print_hdc_error(ft_itoa(i) , cmd_parsing->hdc->break_word);
}

void	heredoc(t_cmd *cmd_parsing, t_env **data, t_minishell *mini)
{
	int	fd;

	fd = open_heredoc_file(O_CREAT | O_RDWR | O_APPEND);
	handle_heredoc_input(cmd_parsing, data, mini, fd);
}
