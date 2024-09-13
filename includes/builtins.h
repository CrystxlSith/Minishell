/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:24:52 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/13 11:53:33 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_env
{
	char	**var;
	int		size;
	int		word_count;
}			t_env;

/* typedef struct s_dirent
{
	char			*file_name;
	char			*current_path;
	char			*previous_path;
	char			*home_path;
	int				numb_elem;
	char			*type;
	struct s_dirent	*next;
	struct s_dirent	*previous;
}					t_dirent; */

//BUILTINS ---> GENERAL
int		builtins(char **input, char **envp);

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
void	cd(char *path, t_env **data);
void	move_to_dir(char *path, t_env **data);

#endif