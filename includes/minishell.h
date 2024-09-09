/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 09:03:41 by kali              #+#    #+#             */
/*   Updated: 2024/09/09 13:56:01 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "token.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>

typedef struct s_minishell
{
    // Ligne tapee dans le terminal
    char    *line_read;
}   t_minishell;

typedef struct s_env
{
	char			**var;
	int				size;
	int				word_count;
}					t_env;

t_token	*tokenize(char *str);
t_token	*create_new_token(t_token_type type, char *data);
void	new_token(t_token **tokens, t_token *new_node);

//BUILTINS ---> ECHO
int		count_words(char **str);
int		get_index(char **str, char *chr);
int		count_letters(char **str);
void	free_all(char **s);
char	*echo(char **input, char **envp);

//BUILTINS ---> PWD
int		find_line(char **envp, char *chr);
char	*get_filepath(char **envp);
void	pwd(char **envp);

//BUILTINS ---> ENV
void	count_env(char **envp, t_env **data);
void	get_env(char **envp, t_env **data);
void	env(t_env **data);
void	initiate_struc(t_env **data, char **envp);

//BUILTINS ---> EXPORT
void	export(char **input, t_env **data);
void	free_rest_tab(char **s, int index);

#endif