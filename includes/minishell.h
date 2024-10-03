/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 09:03:41 by kali              #+#    #+#             */
/*   Updated: 2024/10/03 13:16:25 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "parsing.h"
# include "builtins.h"
# include "pipex.h"
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

# define TRUE 1
# define FALSE 0

/**
 * @file minishell.h
 * @brief Header file for the Minishell project.
 *
 * This file contains the definition of the `t_minishell` structure, which is used
 * to store the state of the Minishell application.
 */

/**
 * @struct s_minishell
 * @brief Structure to hold the state of the Minishell application.
 *
 * The `t_minishell` structure contains the following fields:
 * - `line_read`: A pointer to a string that holds the last line read from the input.
 * - `last_exit_status`: An integer that stores the exit status of the last executed command.
 *
 * @example
 * t_minishell shell;
 * shell.line_read = NULL;
 * shell.last_exit_status = 0;
 */
typedef struct s_minishell
{
	char	*line_read;
	int	last_exit_status;
}			t_minishell;

extern t_minishell minishell;

//LEXER && PARSER
t_lexer	*tokenize(char *str);
void	init_cmd(t_cmd **head, t_cmd **current);
void	create_new_token(t_lexer_type type, char *data, t_lexer **tokens);

void	new_token(t_lexer **tokens, t_lexer *new_node);

//EXECUTION
void	exec_single_cmd(t_cmd **parsing, t_env **data);
void	exec_exit(char **envp);
//BUILTINS ---> GENERAL
int		builtins(t_cmd **parsing, t_env **data);

//Heredoc
int	initiate_hdc_struc(t_cmd *parsing);
char	**ft_realloc_hdc(int new_size, t_cmd **parsing);
void	duplicate_hdc(t_cmd **parsing);
void	fill_heredoc(t_cmd **parsing, int size);
void	heredoc(t_cmd **parsing, t_env **data);

#endif