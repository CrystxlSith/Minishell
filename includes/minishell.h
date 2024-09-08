/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 09:03:41 by kali              #+#    #+#             */
/*   Updated: 2024/09/08 08:42:58 by kali             ###   ########.fr       */
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

typedef struct s_minishell
{
    char    *line_read;
}   t_minishell;


//LEXER && PARSER
t_lexer *tokenize(char *str);
void	init_cmd(t_cmd **head, t_cmd **current);
void create_new_token(t_lexer_type type, char *data, t_lexer **tokens);
void new_token(t_lexer **tokens, t_lexer *new_node);

//BUILTINS ---> ECHO
int		count_words(char **str);
int		get_index(char **str);
int		count_letters(char **str);

//BUILTINS ---> PWD
int		find_line(char **envp);
char	*get_filepath(char **envp);
void	pwd(char **envp);

#endif