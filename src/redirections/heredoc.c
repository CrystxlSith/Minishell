/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:04:40 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/14 13:48:43 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	heredoc_launcher(t_cmd **cmd_parsing, t_env **data, t_minishell *mini)
{
	int			pid;
	int			fd;
	int			status;

	fd = open_heredoc_file(O_CREAT | O_RDWR | O_TRUNC);
	(*cmd_parsing)->hdc->hdc_fd = fd;
	pid = fork();
	if (pid == -1)
		exit(0);
	if (pid == 0)
	{
		while (1)
		{
			init_signals(1);
			mini->line_read = readline("> ");
			if (launcher_exec(mini->line_read, data, \
				cmd_parsing, mini) == -1)
			{
				printf("%s\n", "hdc failure");
				exit(EXIT_FAILURE);
				return ;
			}
			if (mini->line_read[0] == '\0')
			{
				printf("%s\n", "hdc failure");
				free(mini->line_read);
				continue ;
			}
			if (ft_strncmp((*cmd_parsing)->hdc->break_word, mini->line_read, \
				ft_strlen((*cmd_parsing)->hdc->break_word)) == 0)
				exit(EXIT_SUCCESS);
			else
				write_to_heredoc(fd, mini->line_read);
		}
	}
	waitpid(pid, &status, 0);
}
