/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycry <crycry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:07:38 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/10/31 03:23:04 by crycry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# include "parsing.h"

# ifndef EXIT_ARGS_ERR
#  define EXIT_ARGS_ERR "bash: exit: too many arguments\n"
# endif

//BUILTINS ---> EXIT
char	*launch_minishell(t_env *data, char *name);
//BUILTINS ---> ECHO
int		count_words(char **str);
int		get_index(t_env **data, char *chr);
int		count_letters(char **str);
void	free_all(char **s);
int		echo(char **input, t_env **data);
char	*find_in_env(char *input, char **env);

//BUILTINS ---> PWD
char	*get_path(char **envp);
int		pwd(t_cmd **parsing, t_env **data);

//BUILTINS ---> ENV
void	count_env(char **envp, t_env **data);
void	get_env(char **envp, t_env **data);
int		env(t_env **data);
void	initiate_struc_envp(t_env **data, char **envp);

//BUILTINS ---> EXPORT
int		export(char *input, t_env **data);
void	free_rest_tab(char **s, int index);
void	print_tab(t_env **data);
void	update_env_tab_export(char *flag, char *cmd, t_env **data);
char	**ft_realloc_env(int new_size, t_env **data);
int		export_existing(char *flag, t_env **data, char *cmd);
void	duplicate_env(t_env **data, char *cmd);
void	export_new(t_env **data, char *cmd);

//BUILTINS ---> CD
int		file_compliant(char *dir_path);
int		update_env(char *old_path, char *new_path, t_env **data);
int		go_to_path(char *path);
char	*cd_prev_oldpwd(char *current_path, t_env **data);
int		get_dir_len(char *path);
char	*cd_get_prev_path(char *path, char *current_path);
char	*cd_prev_newpwd(char *path, char *current_path);
int		cd_home(char *path, t_env **data);
int		cd_prev(char *path, t_env **data);
int		cd(char *path, t_env **data);
void	move_to_dir(char *path, t_env **data);
char	*format_dir_path(char *path);

//BUILTINS ---> EXPORT
int		unset(char *input, t_env **data);

#endif