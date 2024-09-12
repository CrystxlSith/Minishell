/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:47:29 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/12 10:19:46 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_if_builtins(char *input)
{
	if (ft_strncmp(input, "echo", 5) == 0
		|| ft_strncmp(input, "pwd", 4) == 0
		|| ft_strncmp(input, "env", 4) == 0
		|| ft_strncmp(input, "export", 7) == 0
		|| ft_strncmp(input, "cd", 3) == 0)
		return (TRUE);
	return (FALSE);
}

void	exec_single_cmd(char **input, char **envp)
{
	int	id;

	id = 1;
	if (check_if_builtins(input[0]))
		builtins(input, envp);
	else
		check_cmd_minishell(id, input, envp);
}

/* int	open_dup_mini(int *fd)
{
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		return (-1);
	}
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		close(fd[0]);
		return (-1);
	}
	return (0);
}

void	execute_cmd_minishell(int *fd, char **input, char **envp)
{
	if (open_dup_mini(fd) == -1)
	{
		return ;
	}
	check_cmd_minishell(1, input, envp);
}

void	fork_input_cmd(char **input, t_cmd *cmd, char **envp)
{
	int	fd[2];
	int	pid;

	if (cmd->next == NULL)
		exec_single_cmd(input, envp);
	else
	{
		if (pipe(fd) == -1)
			return ;
		pid = fork();
		if (pid == -1)
			return ;
		if (pid == 0)
			execute_cmd_minishell(fd, input, envp);
		close(fd[0]);
		close(fd[1]);
	}
}
 */