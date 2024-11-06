/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multi_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:23:26 by agiliber          #+#    #+#             */
/*   Updated: 2024/11/05 17:28:23 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_heredoc_pipe(t_cmd *parsing, int *fd)
{
	if (pipe_heredoc(parsing, fd) == -1)
		return (-1);
	return (0);
}

int	handle_first_cmd_pipe(t_cmd *parsing, t_env **data, int *fd)
{
	if (is_redirected_cmd(parsing))
	{
		parsing = parsing->next;
		if (exec_redirection(&parsing, data, 0) == -1)
			return (-1);
		exit(EXIT_SUCCESS);
	}
	else if (open_dup_pipe_out(fd) == -1)
		return (-1);
	return (0);
}

int	handle_middle_cmd_pipe(int *old_fd, int *fd)
{
	if (open_dup_pipe_middle(old_fd, fd) == -1)
		return (-1);
	return (0);
}

int	handle_last_cmd_pipe(int *old_fd)
{
	if (open_dup_pipe_in(old_fd) == -1)
		return (-1);
	return (0);
}

int	is_redirected_cmd(t_cmd *parsing)
{
	return ((parsing->next->str == NULL)
		&& (parsing->next->redir->type == E_REDIR_OUT
			|| parsing->next->redir->type == E_REDIR_APP));
}
