/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:48:17 by agiliber          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/10/29 14:39:06 by agiliber         ###   ########.fr       */
=======
/*   Updated: 2024/10/29 14:57:22 by agiliber         ###   ########.fr       */
>>>>>>> Minishell_AGT
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

extern int	g_sig_status;

typedef struct s_minishell
{
	char	*line_read;
}			t_minishell;

//LEXER && PARSER
int			ft_exit_shell(t_cmd *cmd_parsing, t_env *data, t_lexer *tokens);
t_lexer		*tokenize(char *str);
void		create_new_token(t_lexer_type type, char *data, t_lexer **tokens);
void		new_token(t_lexer **tokens, t_lexer *new_node);
t_cmd		*parser(t_lexer **tokens, t_env **data);

//BUILTINS ---> GENERAL
int			builtins(t_cmd **parsing, t_env **data);

//ft_print_utils
void		print_cmd(t_cmd *head);
void		print_tokens(t_lexer *tokens);
void		print_heredoc(t_heredoc *hdc);

//ft_launch_utils
int			launcher_exec(char *input, t_env **data);
int			start_error(char *input);
void		input_execution(t_env *data, t_cmd *cmd_parsing);
int			generate_minishell_prompt(t_env *data, t_lexer *tokens, \
		t_cmd *cmd_parsing);

//free_utils
void		free_token(t_lexer *token);
void		free_tokens(t_lexer *tokens);
void		free_parsed_cmd(t_cmd *head);
void		free_minishell(t_env *data);
void		free_all_line(t_lexer *tokens, t_cmd *cmd_parsing);
void		free_hdc(t_heredoc *head);

//Heredocs
void		initiate_hdc_struc(t_cmd **parsing);
int			ft_remove(const char *pathname);
int			open_heredoc_file(int flags);
void		write_to_heredoc(int fd, char *line);
int			handle_heredoc(t_cmd **cmd_parsing, t_env **data);
int			handle_readline_error(int fd);
int			exit_failure(int fd);
int			handle_break_word(t_cmd *cmd_parsing, t_env **data);
int			handle_heredoc_input(t_cmd *cmd_parsing, t_env **data);
int			detect_hdc(t_cmd **cmd_parsing);
void		generate_hdc_files(t_cmd **cmd_parsing, int count);
void		remove_hdc_file(void);
void		create_hdc_file(t_cmd *parsing);
t_heredoc	*new_hdc_struc(t_cmd **parsing);
<<<<<<< HEAD
void		print_hdc_error(int i, char *token2);
=======
void		print_hdc_error(int i , char *token2);
>>>>>>> Minishell_AGT

#endif