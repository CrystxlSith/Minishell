/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 09:03:41 by kali              #+#    #+#             */
/*   Updated: 2024/09/04 10:26:08 by agiliber         ###   ########.fr       */
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

t_token	*tokenize(char *str);
t_token	*create_new_token(t_token_type type, char *data);
void	new_token(t_token **tokens, t_token *new_node);

//BUILTINS ---> ECHO
int		count_words(char **str);
int		get_index(char **str);
int		count_letters(char **str);

//BUILTINS ---> PWD
int		find_line(char **envp);
char	*get_filepath(char **envp);
void	pwd(char **envp);

#endif