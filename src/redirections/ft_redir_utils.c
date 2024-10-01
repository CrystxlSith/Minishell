/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariannedubuard <mariannedubuard@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:39:40 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/30 13:19:03 by mariannedub      ###   ########.fr       */
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
	t_cmd	*tmp;

	(void)data;
	tmp = *parsing;
	printf("REDIR IN : %s\n", tmp->redir->data);
	fd_redir = open(tmp->redir->data, O_RDONLY);
	if (fd_redir == -1)
		return ;
	if (open_dup_input(fd_redir) == -1)
		return ;
	exec_single_cmd(parsing, data);
	//exit(0);
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
	//exit(0);
}

void	fork_redirection(int redir, t_cmd **parsing, t_env **data)
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
			if (tmp->redir->type == E_REDIR_IN)
			{
				exec_redir_in(parsing, data);
			}
			else if (tmp->redir->type == E_REDIR_OUT)
			{
				exec_redir_out(parsing, data);
			}
			break ;
		}
		else
		{
			waitpid(pid, &status, 0);
			tmp->redir = tmp->redir->next;
			redir--;
		}
	}
}

void	exec_redirection(t_cmd **parsing, t_env **data)
{
	int	redir;

	redir = (*parsing)->redir_nb;
	fork_redirection(redir, parsing, data);
}
