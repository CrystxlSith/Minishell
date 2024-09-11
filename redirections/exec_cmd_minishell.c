/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:47:29 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/11 11:48:04 by agiliber         ###   ########.fr       */
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
	if (check_if_builtins(input[0]) || check_if_builtins(input[1]))
		builtins(input, envp);
	else
		check_cmd_minishell(id, input, envp);
}

void	fork_input_cmd(char **input, t_cmd *cmd, char **envp)
{
/* 	int	fd[2];
	int	*pid;
 */
	if (cmd->next == NULL)
		exec_single_cmd(input, envp);
/* 	if (pipe(fd) == -1)
		return ;
	fork();
 */
}
