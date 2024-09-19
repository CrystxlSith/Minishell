/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:39:40 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/19 13:47:21 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_redir_in(int index, t_cmd **parsing, t_env **data)
{
	int		fd_redir;
	t_cmd	*tmp;

	tmp = *parsing;
	fd_redir = open(tmp->str[index], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd_redir == -1)
		return ;
	printf("FD REDIR : %d\n", fd_redir);
	if (open_dup_input(fd_redir) == -1)
		return ;
	exec_single_cmd(parsing, data);
}

void	exec_redir_out(int index, t_cmd **parsing, t_env **data)
{
	int		fd_redir;
	t_cmd	*tmp;

	tmp = *parsing;
	printf("BRANCH : %d\n", E_REDIR_OUT);
	printf("tmp->str[index] : %s\n", tmp->str[index]);
	fd_redir = open(tmp->str[index], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd_redir == -1)
		return ;
	printf("FD REDIR : %d\n", fd_redir);
	if (open_dup_output(fd_redir) == -1)
		return ;
	exec_single_cmd(parsing, data);
}

void	exec_redirection(t_cmd **parsing, t_env **data)
{
	t_cmd	*tmp;
	int		index;
	int		redir;
	int		pid;
	int		status;

	tmp = *parsing;
	index = find_index_file(tmp, 0);
	redir = tmp->redir_nb;
	while (redir > 0)
	{
		pid = fork();
		if (pid == -1)
			return ;
		if (pid == 0)
		{
			if (tmp->redir->type == E_REDIR_IN)
				exec_redir_in(index, parsing, data);
			else if (tmp->redir->type == E_REDIR_OUT)
				exec_redir_out(index, parsing, data);
		}
		else
		{
			tmp->redir = tmp->redir->next;
			redir--;
			index = find_index_file(tmp, index);
		}
		waitpid(pid, &status, 0);
	}
}