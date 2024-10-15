/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:04:40 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/15 15:14:37 by agiliber         ###   ########.fr       */
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
	int			pid;
	int			fd;
	int			status;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
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
				}
				else if ((cmd_parsing)->hdc->next == NULL)
				{
					exec_multiple_cmd(&cmd_parsing, data);
					exit(EXIT_SUCCESS);
				}
			}
			write_to_heredoc(fd, mini->line_read);
		}
	}
	waitpid(pid, &status, 0);
} */
