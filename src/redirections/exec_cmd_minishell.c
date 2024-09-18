/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:47:29 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/18 16:27:35 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_index_file(t_cmd *parsing, int i)
{
	while(parsing->str[i])
	{
		if (ft_strncmp(parsing->str[i], "<", 2) == 0
			|| ft_strncmp(parsing->str[i], ">", 2) == 0)
			return (i + 1);
		i++;
	}
	return (-1);
}

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
	if ((*parsing)->redir_nb > 0)
		exec_redirection(parsing, data);
	else
		exec_single_cmd(parsing, data);
}

void	exec_single_cmd(t_cmd **parsing, t_env **data)
{
	if (check_if_builtins((*parsing)->str[0]))
	{
		printf("BUILTIN %s ", (*parsing)->str[0]);
		builtins((*parsing)->str, data);
	}
	else
	{
		printf("Check CMD %s ", (*parsing)->str[0]);
		check_cmd_minishell((*parsing)->str, (*data)->var);
	}
}

void	exec_redirection(t_cmd **parsing, t_env **data)
{
	t_cmd	*tmp;
	int		fd_redir;
	int		index;
	int		redir;

	tmp = *parsing;
	index = find_index_file(tmp, 0);
	printf("INDEX : %d\n", index);
	redir = tmp->redir_nb;
	while (redir > 0)
	{
		if (tmp->redir->type == E_REDIR_IN)
		{
			fd_redir = open(tmp->str[index], O_CREAT | O_RDWR, 0777);
			if (fd_redir == -1)
				return ;
			if (open_dup_input(fd_redir) == -1)
				return ;
		}
		else if (tmp->redir->type == E_REDIR_OUT)
		{
			printf("BRANCH : %d\n", E_REDIR_OUT);
			fd_redir = open(tmp->str[index], O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if (fd_redir == -1)
				return ;
			printf("FD REDIR : %d\n", fd_redir);
			if (open_dup_output(fd_redir) == -1)
				return ;
		}
		tmp->redir = tmp->redir->next;
		redir--;
		index = find_index_file(tmp, index);
	}
	exec_single_cmd(parsing, data);
	close(fd_redir);
}

void	exec_cmd_minishell(t_cmd **parsing, t_env **data)
{
	if ((*parsing)->next == NULL)
		exec_cmd(parsing, data);
	else
		exec_multiple_cmd(parsing, data);
}

int	open_dup_output(int fd_in)
{
	if (dup2(fd_in, STDOUT_FILENO) == -1)
	{
		perror("dup2 fd_in");
		close(fd_in);
		return (-1);
	}
	close(fd_in);
	return (0);
}

int	open_dup_input(int fd_in)
{
	if (dup2(fd_in, STDIN_FILENO) == -1)
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
