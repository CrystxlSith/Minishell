/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_in_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:16:47 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/08 11:14:24 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_multiple_redir_in(t_cmd *tmp, t_env **data)
{
	int		fd_redir;
	int		fd_out;

	(void)data;
	while (tmp->redir->next != NULL)
	{
		fd_redir = open(tmp->redir->data, O_CREAT | O_RDWR | O_TRUNC, 0777);
		if (fd_redir == -1)
			return (perror("open multi redir in "), -1);
		close(fd_redir);
		tmp->redir = tmp->redir->next;
	}
	fd_out = open(tmp->redir->data, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd_out == -1)
		return (perror("open multi redir fd out "), -1);
	if (open_dup_output(fd_out) == -1)
		return (perror("open dup multi redir "), -1);
	return (0);
}

int	exec_redir_in(t_cmd **parsing, t_env **data)
{
	int		fd_redir;
	t_cmd	*tmp;

	tmp = *parsing;
	while (tmp->redir->next != NULL && tmp->redir->next->type == E_REDIR_IN)
		tmp->redir = tmp->redir->next;
	fd_redir = open(tmp->redir->data, O_RDONLY);
	if (fd_redir == -1)
		return (perror("infile "), -1);
	if (open_dup_input(fd_redir) == -1)
		return (perror("open_dup infile "), -1);
	if (tmp->redir->next != NULL && tmp->redir->next->type == E_REDIR_OUT)
	{
		tmp->redir = tmp->redir->next;
		if (exec_multiple_redir_in(tmp, data) == -1)
			return (perror("exec_multiple_redir_in "), -1);
	}
	exec_single_cmd(parsing, data);
	exit(0);
}
