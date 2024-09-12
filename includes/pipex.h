/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 10:23:28 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/12 10:54:46 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdbool.h>
# include <limits.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>

void	execute_cmd1(int *fd, char **arg, char **envp);
void	check_cmd_minishell(int id, char **av, char **envp);
char	*get_filepath(char **av, char **envp);
void	execute_cmd2(int *fd, char **arg, char **envp);
int		find_line(char **envp);
void	free_all(char **s);
int		open_dup_file1(int file_fd, int *fd);
int		open_dup_file2(int *fd, int file_fd);
int		check_space(char *str);
void	close_fd(int *fd);
int		check_input(char **str);

#endif