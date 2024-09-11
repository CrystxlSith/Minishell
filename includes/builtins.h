/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:24:52 by agiliber          #+#    #+#             */
/*   Updated: 2024/09/11 11:43:05 by agiliber         ###   ########.fr       */
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

typedef struct s_dirent
{
	char			*file_name;
	char			*current_path;
	char			*previous_path;
	char			*home_path;
	int				numb_elem;
	char			*type;
	struct s_dirent	*next;
	struct s_dirent	*previous;
}					t_dirent;

//BUILTINS ---> GENERAL
int		builtins(char **input, char **envp);

//BUILTINS ---> ECHO
int		count_words(char **str);
int		get_index(t_env **data, char *chr);
int		count_letters(char **str);
void	free_all(char **s);
char	*echo(char **input, char **envp);

//BUILTINS ---> PWD
/* int		find_line(char **envp, char *chr); */
char	*get_path(char **envp);
void	pwd(char **envp);

//BUILTINS ---> ENV
void	count_env(char **envp, t_env **data);
void	get_env(char **envp, t_env **data);
void	env(t_env **data);
void	initiate_struc(t_env **data, char **envp);

//BUILTINS ---> EXPORT
void	export(char **input, t_env *data);
void	free_rest_tab(char **s, int index);
void	print_tab(t_env **data);

//BUILTINS ---> CD
char	*get_home_path(char **envp);
char	*get_previous_path(char **envp);
void	initiate_dir_list(t_dirent **dir);
void	fill_dir_list(t_dirent **dir, char **envp);
char	*file_compliant(char **av);
void	cd(char	**av, t_dirent **dir, t_env **data);
void	print_lst(t_dirent **dir);

#endif