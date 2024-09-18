/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 10:23:28 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/18 16:22:21 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdbool.h>
# include <limits.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>

void	check_cmd_minishell(char **av, char **envp);
char	*get_filepath(char **av, char **envp);
int		find_line(char **envp);
void	free_all(char **s);
int		check_space(char *str);
void	close_fd(int *fd);
int		check_input(char **str);
int		check_if_builtins(char *input);
void	exec_cmd(t_cmd **parsing, t_env **data);
void	exec_single_cmd(t_cmd **parsing, t_env **data);
void	exec_redirection(t_cmd **parsing, t_env **data);
void	exec_cmd_minishell(t_cmd **parsing, t_env **data);
int		open_dup_output(int fd_in);
int		open_dup_input(int fd_in);
void	execute_fork(t_cmd **parsing, t_env **data);
void	exec_multiple_cmd(t_cmd **parsing, t_env **data);
#endif