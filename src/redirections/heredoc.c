/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:04:40 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/15 17:41:28 by agiliber         ###   ########.fr       */
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

/* void	heredoc(t_cmd *cmd_parsing, t_env **data, t_minishell *mini)
{
	int			fd;
	int			status;
	int	pid;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		fd = open_heredoc_file(O_CREAT | O_RDWR | O_TRUNC);
		if (fd == -1)
		{
			perror("open heredoc");
			exit(EXIT_FAILURE);
		}
		while (1)
		{
			mini->line_read = readline("> ");
			if (ft_strncmp((cmd_parsing)->hdc->break_word, mini->line_read, \
				ft_strlen((cmd_parsing)->hdc->break_word)) == 0)
			{
				free(mini->line_read);
				break ;
			}
			write_to_heredoc(fd, mini->line_read);
			free(mini->line_read);
		}
		//close(fd);
		(cmd_parsing)->hdc = (cmd_parsing)->hdc->next;
		if ((cmd_parsing)->hdc->next == NULL)
			exec_multiple_cmd(&cmd_parsing, data);
	}
	waitpid(pid, &status, 0);
}
 */

void	heredoc(t_cmd *cmd_parsing, t_env **data, t_minishell *mini)
{
	int	fd;

	while (1)
	{
		init_signals(1);
		fd = open_heredoc_file(O_CREAT | O_RDWR | O_APPEND);
		mini->line_read = readline("> ");
		if (launcher_exec(mini->line_read, data, &cmd_parsing, mini) == -1)
			exit(EXIT_FAILURE);
		if (mini->line_read[0] == '\0')
		{
			free(mini->line_read);
			continue ;
		}
		if (ft_strncmp((cmd_parsing)->hdc->break_word, mini->line_read, \
			ft_strlen((cmd_parsing)->hdc->break_word)) == 0)
		{
			if ((cmd_parsing)->hdc->next != NULL)
			{
				ft_remove("/tmp/heredoc.txt");
				(cmd_parsing)->hdc = (cmd_parsing)->hdc->next;
				break ;
			}
			else if ((cmd_parsing)->hdc->next == NULL)
			{
				close(fd);
				exec_multiple_cmd(&cmd_parsing, data);
					break ;
			}
		}
		write_to_heredoc(fd, mini->line_read);
	}
}
