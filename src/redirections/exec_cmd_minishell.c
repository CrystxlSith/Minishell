/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:47:29 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/17 15:30:41 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_if_builtins(char *input)
{
	if (ft_strncmp(input, "echo", 4) == 0
		|| ft_strncmp(input, "pwd", 3) == 0
		|| ft_strncmp(input, "env", 3) == 0
		|| ft_strncmp(input, "export", 6) == 0
		|| ft_strncmp(input, "cd", 2) == 0
		|| ft_strncmp(input, "unset", 5) == 0)
		return (TRUE);
	return (FALSE);
}

void	exec_cmd(t_cmd **parsing, t_env **data)
{
	int	fd[2];

	if ((*parsing)->redir_nb > 0)
	{
		printf("Exec cmd here_doc %d\n", (*parsing)->redir_nb);
		exec_redirection(parsing, data, fd);
	}
	else
		exec_single_cmd(parsing, data);
	close_fd(fd);
}

void	exec_single_cmd(t_cmd **parsing, t_env **data)
{
	if (check_if_builtins((*parsing)->str[0]))
		builtins((*parsing)->str, data);
	else
		check_cmd_minishell(1, (*parsing)->str, (*data)->var);
}

void	exec_redirection(t_cmd **parsing, t_env **data, int *fd)
{
	t_cmd	*tmp;
	int		fd_redir;
	int		index;
	int		redir;

	tmp = *parsing;
	index = 2;
	redir = tmp->redir_nb;
	while (redir > 0)
	{
		if (tmp->redir->type == E_REDIR_IN)
		{
			tmp->redir = tmp->redir->prev;
			fd_redir = open(tmp->str[index], O_CREAT | O_RDWR, 0777);
			if (fd_redir == -1)
				return ;
			open_dup_output(fd, fd_redir);
			exec_single_cmd(&tmp, data);
		}
		else if (tmp->redir->type == E_REDIR_OUT)
		{
			printf("BRANCH : %d\n", E_REDIR_OUT);
			fd_redir = open(tmp->str[index], O_RDWR | O_CREAT, 0777);
			if (fd_redir == -1)
				return ;
			printf("FD REDIR : %d\n", fd_redir);
			open_dup_input(fd, fd_redir);
			exec_single_cmd(&tmp, data);
		}
		tmp->redir = tmp->redir->next;
		redir--;
		index = index + 2;
	}
	close(fd_redir);
}

void	exec_cmd_minishell(t_cmd **parsing, t_env **data)
{
	if ((*parsing)->next == NULL)
		exec_cmd(parsing, data);
	else
		exec_multiple_cmd(parsing, data);
}

int	open_dup_input(int *fd, int fd_in)
{
	if (dup2(fd[0], STDIN_FILENO) == -1)
		return (-1);
	if (dup2(fd_in, STDOUT_FILENO) == -1)
	{
		close(fd[0]);
		return (-1);
	}
	return (0);
}

int	open_dup_output(int *fd, int fd_in)
{
	if (dup2(fd_in, STDIN_FILENO) == -1)
	{
		return (-1);
	}
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		return (-1);
	}
	close(fd_in);
	return (0);
}

void	execute_fork(t_cmd **parsing, t_env **data)
{
	int	fd[2];
	int	pid;
	int	status;

	if (pipe(fd) == -1)
		return ;
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		if ((*parsing)->next != NULL)
			dup2(fd[1], STDOUT_FILENO);
		exec_cmd_minishell(parsing, data);
	}
	else
	{
		if ((*parsing)->next != NULL)
			dup2(fd[0], STDIN_FILENO);
	}
	close_fd(fd);
	waitpid(pid, &status, 0);
}

void	exec_multiple_cmd(t_cmd **parsing, t_env **data)
{
	t_cmd	*tmp;

	tmp = *parsing;
	while (tmp != NULL)
	{
		execute_fork(parsing, data);
		tmp = tmp->next;
	}
}
