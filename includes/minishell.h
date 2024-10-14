/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 09:03:41 by kali              #+#    #+#             */
/*   Updated: 2024/10/14 15:59:29 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "builtins.h"

# include "../libft/libft.h"
# include "parsing.h"
# include "builtins.h"
# include "pipex.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>
# include <sys/stat.h>
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
}			t_minishell;

extern int	g_sig_status;

//LEXER && PARSER
int    ft_exit_shell(t_cmd *cmd_parsing, t_env *data, t_lexer *tokens);


t_lexer	*tokenize(char *str);
void	init_cmd(t_cmd **head, t_cmd **current);
void	create_new_token(t_lexer_type type, char *data, t_lexer **tokens);
void	new_token(t_lexer **tokens, t_lexer *new_node);

//BUILTINS ---> GENERAL
int		builtins(t_cmd **parsing, t_env **data);

//Heredocs
int		initiate_hdc_struc(t_cmd **parsing);
int		ft_remove(const char *pathname);
int		open_heredoc_file(int flags);
void	write_to_heredoc(int fd, char *line);
void	heredoc_launcher(t_cmd **cmd_parsing, t_env **data, t_minishell *mini);
int		launcher_exec(char *input, t_env **data, t_cmd **parsing, t_minishell *minishell);
void	handle_heredoc(t_cmd **cmd_parsing, t_env **data, t_minishell *mini);

#endif