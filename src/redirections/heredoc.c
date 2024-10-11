/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:04:40 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/11 10:58:25 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	heredoc(int index, t_minishell *mini, t_cmd **parsing, t_env **data)
{
	int	fd;
	int	i;

	i = index - (*parsing)->hdc->hdc_nb;
	if ((*parsing)->hdc->hdc_nb > 1)
	{
		if (check_break_word(*parsing, mini, i))
			(*parsing)->hdc->hdc_nb--;
		fd = open_heredoc_file(O_CREAT | O_RDWR | O_TRUNC);
		write_to_heredoc(fd, mini->line_read);
		close(fd);
	}
	else
	{
		fd = open_heredoc_file(O_CREAT | O_RDWR | O_APPEND);
		if (check_break_word(*parsing, mini, i))
		{
			(*parsing)->hdc->input_nbr = fd;
			(*parsing)->redir_nb--;
			exec_multiple_cmd(parsing, data);
			exit(EXIT_SUCCESS);
		}
		write_to_heredoc(fd, mini->line_read);
		(*parsing)->hdc->input_nbr = fd;
		close(fd);
	}
}
