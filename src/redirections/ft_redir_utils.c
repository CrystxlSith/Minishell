/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:39:40 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/01 14:21:31 by agiliber         ###   ########.fr       */
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

void	exec_redir_in(t_cmd **parsing, t_env **data)
{
	int		fd_redir;
	int		fd_out;
	t_cmd	*tmp;
	int		count;

	(void)data;
	tmp = *parsing;
	fd_out = -1;
	count = 0;
	printf("REDIR IN : %s\n", tmp->redir->data);
	fd_redir = open(tmp->redir->data, O_RDONLY);
	if (fd_redir == -1)
		return ;
	if (open_dup_input(fd_redir) == -1)
		return ;
	if (tmp->redir->next->type == E_REDIR_OUT)
	{
		tmp->redir = tmp->redir->next;
		count = tmp->redir_nb - 1;
		while (tmp->redir != NULL)
		{
			printf("REDIR data : %s\n", tmp->redir->data);
			if (tmp->redir->next != NULL)
			{
				printf("Count data : %d\n", count);
				create_file_out(tmp->redir->data, count);
				tmp->redir = tmp->redir->next;
				count--;
			}
			else
			{
				printf("OPEN : %s\n", "open final file");
				fd_out = open(tmp->redir->data, O_CREAT | O_RDWR | O_TRUNC, 0777);
				if (fd_out == -1)
					return ;
				if (open_dup_output(fd_out) == -1)
					return ;
			}
		}
	}
	exec_single_cmd(parsing, data);
	exit(0);
}

void	exec_redir_out(t_cmd **parsing, t_env **data)
{
	int		fd_redir;
	t_cmd	*tmp;

	(void)data;
	tmp = *parsing;
	printf("REDIR OUT : %s\n", tmp->redir->data);
	fd_redir = open(tmp->redir->data, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd_redir == -1)
		return ;
	if (open_dup_output(fd_redir) == -1)
		return ;
	exec_single_cmd(parsing, data);
	exit(0);
}

void	create_file_out(char *file, int end)
{
	int		fd_redir;

	fd_redir = open(file, O_CREAT, 0777);
	if (fd_redir == -1)
		return ;
	close(fd_redir);
	if (end == 1)
		exit(0);
}

void	fork_redirection(int redir, t_cmd **parsing, t_env **data)
{
	int		pid;
	int		status;
	t_cmd	*tmp;
	int		trigger;

	trigger = 1;
	(void)redir;
	tmp = *parsing;
	while (tmp->redir_nb > 0)
	{
		pid = fork();
		if (pid == -1)
			return ;
		if (pid == 0)
		{
			if (tmp->redir->type == E_REDIR_IN)
				trigger = 1;
			if (tmp->redir->type == E_REDIR_IN)
				exec_redir_in(parsing, data);
			else if (tmp->redir->type == E_REDIR_OUT)
			{
				if (tmp->redir_nb == 1)
					exec_redir_out(parsing, data);
				else
					create_file_out(tmp->redir->data, tmp->redir_nb);
			}
		}
		else
		{
			waitpid(pid, &status, 0);
			if (trigger == 1)
				tmp->redir_nb--;
			tmp->redir = tmp->redir->next;
			tmp->redir_nb--;
		}
	}
}

void	exec_redirection(t_cmd **parsing, t_env **data)
{
	int	redir;

	redir = (*parsing)->redir_nb;
	fork_redirection(redir, parsing, data);
}
