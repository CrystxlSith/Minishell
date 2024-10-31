/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_out_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:15:48 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/22 11:33:07 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_redir_out(t_cmd **parsing, t_env **data)
{
	int		fd_redir;
	t_cmd	*tmp;

	tmp = *parsing;
	if (tmp->redir->type == E_REDIR_APP)
		fd_redir = open(tmp->redir->data, O_CREAT | O_RDWR | O_APPEND, 0777);
	else
		fd_redir = open(tmp->redir->data, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd_redir == -1)
		return (perror("outfile "), -1);
	if (open_dup_output(fd_redir) == -1)
		return (perror("open_dup outfile "), -1);
	if ((*parsing)->str == NULL)
		exit(0);
	exec_single_cmd(parsing, data);
	exit(0);
}

int	create_file_out(char *file, t_cmd **parsing)
{
	int		fd_redir;

	if ((*parsing)->redir->type == E_REDIR_APP)
		fd_redir = open(file, O_CREAT | O_RDWR | O_APPEND, 0777);
	else
		fd_redir = open(file, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd_redir == -1)
		return (perror("create outfile "), -1);
	ft_putstr_fd("", fd_redir);
	close(fd_redir);
	return (0);
}

int	handle_redir_out(t_cmd *tmp, t_cmd **parsing, t_env **data)
{
	if (tmp->redir_nb == 1)
	{
		if (exec_redir_out(parsing, data) == -1)
			return (perror("exec_redir_out "), -1);
	}
	else
	{
		if (create_file_out(tmp->redir->data, parsing) == -1)
			return (perror("create_file_out "), -1);
	}
	return (0);
}
