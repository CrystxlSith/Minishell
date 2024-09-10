/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 09:03:41 by kali              #+#    #+#             */
/*   Updated: 2024/09/10 17:42:53 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "parsing.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>
# include <sys/types.h>
# include <dirent.h>


extern int signal;

typedef struct s_minishell
{
	char	*line_read;
}			t_minishell;

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

//LEXER && PARSER
t_lexer	*tokenize(char *str);
void	init_cmd(t_cmd **head, t_cmd **current);
void	create_new_token(t_lexer_type type, char *data, t_lexer **tokens);
void	new_token(t_lexer **tokens, t_lexer *new_node);

int	builtins(int ac, char **input, char **envp);

//BUILTINS ---> ECHO
int		count_words(char **str);
int		get_index(t_env **data, char *chr);
int		count_letters(char **str);
void	free_all(char **s);
char	*echo(char **input, char **envp);

//BUILTINS ---> PWD
/* int		find_line(char **envp, char *chr); */
char	*get_filepath(char **envp);
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
void	cd(int ac, char	**av, t_dirent **dir, char **envp);

#endif