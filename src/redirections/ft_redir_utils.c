/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:39:40 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/19 15:31:06 by agiliber         ###   ########.fr       */
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
	if (open_dup_input(fd_redir) == -1)
		return ;
	exec_single_cmd(parsing, data);
}

void	exec_redir_out(int index, t_cmd **parsing, t_env **data)
{
	int		fd_redir;
	t_cmd	*tmp;

	tmp = *parsing;
	fd_redir = open(tmp->str[index], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd_redir == -1)
		return ;
	if (open_dup_output(fd_redir) == -1)
		return ;
	exec_single_cmd(parsing, data);
}

void	fork_redirection(int index, int redir, t_cmd **parsing, t_env **data)
{
	int		pid;
	int		status;
	t_cmd	*tmp;

	tmp = *parsing;
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
			waitpid(pid, &status, 0);
			tmp->redir = tmp->redir->next;
			index = find_index_file(tmp, index);
		}
		redir--;
	}
}

void	exec_redirection(t_cmd **parsing, t_env **data)
{
	int	index;
	int	redir;

	index = find_index_file((*parsing), 0);
	redir = (*parsing)->redir_nb;
	fork_redirection(index, redir, parsing, data);
}
