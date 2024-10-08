/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_out_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:15:48 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/08 10:38:17 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_redir_out(t_cmd **parsing, t_env **data)
{
	int		fd_redir;
	t_cmd	*tmp;

	tmp = *parsing;
	fd_redir = open(tmp->redir->data, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd_redir == -1)
		return (perror("outfile "), -1);
	if (open_dup_output(fd_redir) == -1)
		return (perror("open_dup outfile "), -1);
	exec_single_cmd(parsing, data);
	exit(0);
}

int	create_file_out(char *file)
{
	int		fd_redir;

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
		if (create_file_out(tmp->redir->data) == -1)
			return (perror("create_file_out "), -1);
	}
	return (0);
}
