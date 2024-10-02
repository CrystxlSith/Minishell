/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:07:38 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/10/02 15:19:26 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

typedef struct s_env
{
	char	**var;
	int		size;
}			t_env;

//BUILTINS ---> ECHO
int		count_words(char **str);
int		get_index(t_env **data, char *chr);
int		count_letters(char **str);
void	free_all(char **s);
void	echo(char **input, t_env **data);
char	*find_in_env(char *input, char **env);

//BUILTINS ---> PWD
char	*get_path(char **envp);
void	pwd(t_env **data);

//BUILTINS ---> ENV
void	count_env(char **envp, t_env **data);
void	get_env(char **envp, t_env **data);
void	env(t_env **data);
void	initiate_struc_envp(t_env **data, char **envp);

//BUILTINS ---> EXPORT
void	export(char *input, t_env **data);
void	free_rest_tab(char **s, int index);
void	print_tab(t_env **data);
void	update_env_tab_export(char *flag, char *cmd, t_env **data);
char	**ft_realloc_env(int new_size, t_env **data);
void	export_existing(char *flag, t_env **data, char *cmd);
void	duplicate_env(t_env **data, char **input, char *cmd);
void	export_new(t_env **data, char *cmd);

//BUILTINS ---> CD
int		file_compliant(char *dir_path);
void	update_env(char *old_path, char *new_path, t_env **data);
int		go_to_path(char *path);
char	*cd_prev_oldpwd(char *current_path, t_env **data);
int		get_dir_len(char *path);
char	*cd_get_prev_path(char *path, char *current_path);
char	*cd_prev_newpwd(char *path, char *current_path);
void	cd_home(char *path, t_env **data);
void	cd_next(char *path, t_env **data);
void	cd_prev(char *path, t_env **data);
char	*cd(char *path, t_env **data);
void	move_to_dir(char *path, t_env **data);
char	*format_dir_path(char *path);

//BUILTINS ---> EXPORT
void	unset(char *input, t_env **data);

#endif