/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:07:38 by jopfeiff          #+#    #+#             */
<<<<<<< HEAD
<<<<<<< HEAD
/*   Updated: 2024/10/18 11:02:59 by agiliber         ###   ########.fr       */
=======
/*   Updated: 2024/10/21 15:34:13 by agiliber         ###   ########.fr       */
>>>>>>> Minishell_AGT
=======
/*   Updated: 2024/10/18 15:13:56 by jopfeiff         ###   ########.fr       */
>>>>>>> 0f2fb0de3936a87fb5364b63e3d089244d360d71
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# include "parsing.h"
<<<<<<< HEAD

# ifndef EXIT_ARGS_ERR
#  define EXIT_ARGS_ERR "bash: exit: too many arguments\n"
# endif
=======
>>>>>>> Minishell_AGT

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
int	export_existing(char *flag, t_env **data, char *cmd);
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
void	replace_dollar(char **input, char *res, t_env **data);
void	rep_d(t_lexer *tmp, char *res, t_env **data);
int		handle_question(char **res, char *tmp, int *i, t_env **data);
t_cmd	*parser(t_lexer **tokens, t_env **data);
void	handle_env_value(char **res, char *tmp, int *i, t_env **data);
#endif