/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:39:40 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/23 14:33:05 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_line(char **envp)
{
	int	index;

	index = 0;
	while (envp[index])
	{
		if (ft_strncmp(envp[index], "PATH=", 5) == 0)
			break ;
		index++;
	}
	return (index);
}

void	exec_redir_in(int index, t_cmd **parsing, t_env **data)
{
	int		fd_redir;
	t_cmd	*tmp;

	tmp = *parsing;
	printf("REDIR IN : %s\n", tmp->str[index]);
	fd_redir = open(tmp->str[index], O_CREAT | O_RDWR, 0777);
	if (fd_redir == -1)
		return ;
	if (open_dup_input(fd_redir) == -1)
		return ;
	exec_single_cmd(parsing, data);
	exit(0);
}

void	exec_redir_out(int index, t_cmd **parsing, t_env **data)
{
	int		fd_redir;
	t_cmd	*tmp;

	tmp = *parsing;
	printf("REDIR OUT : %s\n", tmp->str[index]);
	fd_redir = open(tmp->str[index], O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd_redir == -1)
		return ;
	if (open_dup_output(fd_redir) == -1)
		return ;
	exec_single_cmd(parsing, data);
	exit(0);
}

void	fork_redirection(int index, int redir, t_cmd **parsing, t_env **data)
{
	int		pid;
	int		status;
	t_cmd	*tmp;
	int		trigger;

	trigger = 0;
	tmp = *parsing;
	while (redir > 0)
	{
		pid = fork();
		if (pid == -1)
			return ;
		if (pid == 0)
		{
			printf("TRIGGER : %d\n", trigger);
			if (tmp->redir->next != NULL)
				tmp->redir = tmp->redir->next;
			if (trigger == 1)
			{
				printf("TRIGGER 1 : %d\n", trigger);
				tmp->redir = tmp->redir->prev;
			}
			printf("REDIR NB : %d\n", redir);
			printf("REDIR DATA : %s\n", tmp->redir->data);
			printf("REDIR TYPE : %u\n", tmp->redir->type);
			if (tmp->redir->type == E_REDIR_IN)
				exec_redir_in(index, parsing, data);
			else if (tmp->redir->type == E_REDIR_OUT)
				exec_redir_out(index, parsing, data);
		}
		else
		{
			waitpid(pid, &status, 0);
			if (trigger == 0)
				trigger = 1;
			printf("REDIR NEXT DATA : %s\n", tmp->redir->data);
			index = find_index_file(tmp, index);
			printf("INDEX : %d\n", index);
			redir--;
		}
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
