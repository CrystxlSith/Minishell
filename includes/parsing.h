/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:32:22 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/29 13:04:31 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft.h"
# include "minishell.h"
# include "builtins.h"
# include <stdbool.h>
# include <limits.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# define SPACE_CHAR "|<>"
# define IS_TOKEN "\"'|<>&"
# define IS_REDIRECTION "<>"
# define LEX_ERR "minishell: syntax error near unexpected token "

// Token types
typedef enum s_lexer_type
{
	E_CMD,
	E_ARG,
	E_HEREDOC,
	E_REDIR_IN,
	E_REDIR_OUT,
	E_OPTIONS,
	E_REDIR_DEL,
	E_AMPERSAND,
	E_REDIR_APP,
	E_PIPE,
	E_S_QUOTE,
	E_D_QUOTE,
	E_UNKNOWN,
	END,
	E_SPACE,
}	t_lexer_type;

// Env viariables
typedef struct s_env
{
	char	**var;
	int		size;
	char	*pwd;
	char	*old_pwd;
}			t_env;

// Token structure
typedef struct s_lexer
{
	t_lexer_type	type;
	int				index;
	char			*data;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}					t_lexer;

// Heredoc
typedef struct s_heredoc
{
	int					hdc_fd;
	char				*file_name;
	int					trigger;
	int					hdc_count;
	t_lexer				*redir;
	char				*break_word;
	char				**command;
	struct s_heredoc	*next;
	struct s_heredoc	*prev;
}						t_heredoc;

// Parse in command, separated by pipes
typedef struct s_cmd
{
	int				redir_nb;
	int				hdc_count;
	int				index;
	int				elem_nb;
	char			**str;
	char			*here_doc;
	t_heredoc		*hdc;
	t_lexer			*redir;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

int		check_quotes(char *str);
int		is_cmd(t_lexer_type type);
int		is_quote(t_lexer_type type);
int		add_count_elem(char **data);
int		lex_error(char *input);
int		pipes_err(t_lexer *head);
int		is_redirection(t_lexer_type type);
void	handle_redirection(t_lexer **token, t_cmd *cmd);
void	redir_handler(t_lexer **token, char **str);
void	space_handler(t_lexer **tokens, char **str);
void	init_replace_dollar(int *i, int *j, char **res);
void	add_heredoc(t_lexer **token, t_cmd *current);
t_cmd	*create_new_cmd(void);
void	init_cmd(t_cmd **head, t_cmd **current);
void	setup_child_signals(void);
int		add_count_elem(char **data);
void	init_signals(int is_heredoc);
void	remove_next_space(t_lexer **tmp);
void	print_cmd(t_cmd *head);
void	print_error(char *error, char *token);
int		handle_number(char **input, int *i, char *tmp, char *tmp2);
int		loop_while_dollar(char **input, char **tmp, int i, char *tmp2);
char	*build_res(char *res, int i, int j, char **input);
void	add_to_cmd(char *data, t_cmd *current);
char	**env_find(char *input);
char	*build_res(char *res, int i, int j, char **input);
void	init_temp(char **tmp, char **tmp2);
char	**add_data_to_tab(char *data);
t_lexer	*remove_space_tokens(t_lexer *head);
void	add_index_to_token(t_lexer *tokens);
void	pipe_handler(t_lexer **tokens, char **str);
void	fill_nbr_element(t_cmd **parsing);
t_cmd	*create_new_cmd(void);
t_lexer	*find_last(t_lexer *node);
void	fill_nbr_element(t_cmd **parsing);
void	handle_env_value(char **res, char *tmp, int *i, t_env **data);
int		handle_question(char **res, int *i, char **input, int *j);
void	rep_d(t_lexer *tmp, char *res, t_env **data);
void	replace_dollar(char **input, char *res, t_env **data);

#endif