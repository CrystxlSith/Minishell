/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 10:23:28 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/19 14:31:40 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdbool.h>
# include <limits.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>

// exec_cmd_minishell
void	execute_fork(t_cmd **parsing, t_env **data);
void	exec_cmd(t_cmd **parsing, t_env **data);
void	exec_single_cmd(t_cmd **parsing, t_env **data);
void	exec_multiple_cmd(t_cmd **parsing, t_env **data);
void	exec_cmd_minishell(t_cmd **parsing, t_env **data);

// ft_pipping_utils
void	close_fd(int *fd);
int		check_if_builtins(char *input);
int		find_index_file(t_cmd *parsing, int i);
int		open_dup_output(int fd_in);
int		open_dup_input(int fd_in);

// get_path_cmd
char	*get_filepath(char **av, char **envp);
char	**get_filepath_norm(char **envp);
int		find_line(char **envp);
char	**format_cmd(char **cmd);
void	check_cmd_minishell(int redir_nb, char **cmd, char **envp);

// ft_redir_utils
void	exec_redir_in(int index, t_cmd **parsing, t_env **data);
void	exec_redir_out(int index, t_cmd **parsing, t_env **data);
void	fork_redirection(int index, int redir, t_cmd **parsing, t_env **data);
void	exec_redirection(t_cmd **parsing, t_env **data);

#endif