/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:47:29 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/16 15:12:59 by agiliber         ###   ########.fr       */
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

	tmp = *parsing;
	print_lexers(tmp->redir);
	while (tmp->redir != NULL)
	{
		printf("REDIR %s\n", tmp->redir->data);
		if (tmp->redir->type == E_REDIR_IN)
		{
			tmp->redir = tmp->redir->prev;
			fd_redir = open(tmp->redir->prev->data, O_RDWR | O_CREAT, 0777);
			if (fd_redir == -1)
				return ;
			open_dup_input(fd, fd_redir);
			exec_single_cmd(&tmp, data);
		}
		else if (tmp->redir->type == E_REDIR_OUT)
		{
			fd_redir = open(tmp->redir->next->data, O_RDWR | O_CREAT, 0777);
			if (fd_redir == -1)
				return ;
			open_dup_output(fd, fd_redir);
			exec_single_cmd(&tmp, data);
		}
		tmp->redir = tmp->redir->next;
	}
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
	{
		close(fd[0]);
		return (-1);
	}
	if (dup2(fd_in, STDOUT_FILENO) == -1)
	{
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
		exec_redirection(parsing, data, fd);
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
	while ((*parsing) != NULL)
	{
		execute_fork(parsing, data);
		(*parsing) = (*parsing)->next;
	}
}
