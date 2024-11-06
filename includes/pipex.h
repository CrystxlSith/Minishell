/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycry <crycry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:08:00 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/11/06 20:53:07 by crycry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "minishell.h"
# include <stdbool.h>
# include <limits.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>

// exec_cmd_minishell
int		execute_fork(t_cmd **parsing, t_env **data);
int		exec_cmd(t_cmd **parsing, t_env **data);
int		exec_single_cmd(t_cmd **parsing, t_env **data);
int		exec_multiple_cmd(t_cmd **parsing, t_env **data);
int		exec_cmd_minishell(t_cmd **parsing, t_env **data);

// ft_pipping_utils
void	close_fd(int *fd);
int		check_if_builtins(char *input);
int		find_index_file(t_cmd *parsing, int i);
int		open_dup_output(int fd_in);
int		open_dup_input(int fd_in);

// get_path_cmd
char	*get_filepath(char **av, char **envp);
char	**get_filepath_norm(char **envp);
int		check_cmd_minishell(t_cmd **parsing, char **envp, t_env **data);
int		execve_cmd(char **cmd, char **envp, t_env **data);

// ft_redir_utils
int		fork_redirection(t_cmd **parsing, t_env **data);
int		exec_redirection(t_cmd **parsing, t_env **data, int trigger);

// ft_redir_in_utils
int		exec_redir_in(t_cmd **parsing, t_env **data);
int		exec_multiple_redir_in(t_cmd *tmp, t_env **data);

// ft_redir_out_utils
int		exec_redir_out(t_cmd **parsing, t_env **data);
int		create_file_out(char *file, t_cmd **parsing);
int		handle_redir_out(t_cmd *tmp, t_cmd **parsing, t_env **data);

// ft_multi_piping_utils
int		open_dup_pipe_out(int *fd);
int		open_dup_pipe_in(int *fd);
int		open_dup_pipe_middle(int *fd_in, int *fd_out);
int		pipe_multiple_cmd(t_cmd *parsing, t_env **data, int *fd, int *old_fd);
int		create_pipe_if_needed(t_cmd *tmp, int *current_fd);
void	update_parent_descriptors(t_cmd *tmp, int *current_fd, int *old_fd);

// ft_multipipe.c
int		handle_heredoc_pipe(t_cmd *parsing, int *fd);
int		handle_first_cmd_pipe(t_cmd *parsing, t_env **data, int *fd);
int		handle_middle_cmd_pipe(int *old_fd, int *fd);
int		handle_last_cmd_pipe(int *old_fd);
int		is_redirected_cmd(t_cmd *parsing);

// ft_pipe_dc
int		open_dup_pipe_hdc(int *fd, int fd_hdc);
int		pipe_heredoc(t_cmd *parsing, int *fd);
int		find_nbr_cmd(t_cmd **parsing);

#endif