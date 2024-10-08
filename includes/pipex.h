/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:08:00 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/10/08 11:07:00 by agiliber         ###   ########.fr       */
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
int		check_cmd_minishell(t_cmd **parsing, char **envp);

// ft_redir_utils
int		fork_redirection(t_cmd **parsing, t_env **data);
int		exec_redirection(t_cmd **parsing, t_env **data, int trigger);

// ft_redir_in_utils
int		exec_redir_in(t_cmd **parsing, t_env **data);
int		exec_multiple_redir_in(t_cmd *tmp, t_env **data);

// ft_redir_out_utils
int		exec_redir_out(t_cmd **parsing, t_env **data);
int		create_file_out(char *file);
int		handle_redir_out(t_cmd *tmp, t_cmd **parsing, t_env **data);

// ft_multi_piping_utils
int		open_dup_pipe_out(int *fd);
int		open_dup_pipe_in(int *fd);
int		pipe_multiple_cmd(t_cmd *parsing, t_env **data, int *fd, int *old_fd);
int		create_pipe_if_needed(t_cmd *tmp, int *current_fd);
void	update_parent_descriptors(t_cmd *tmp, int *current_fd, int *old_fd);

#endif