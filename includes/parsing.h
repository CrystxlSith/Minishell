/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycry <crycry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 10:51:59 by kali              #+#    #+#             */
/*   Updated: 2024/09/28 14:15:55 by crycry           ###   ########.fr       */
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
	E_CMD, //*str
	E_ARG,
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

// Token structure
typedef struct s_lexer
{
	t_lexer_type	type;
	int				index;
	char			*data;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}					t_lexer;

// Parse in command, separated by pipes
typedef struct s_cmd
{
	int				redir_nb;
	int				index;
	int				elem_nb;
	char			**str;
	char			*here_doc;
	t_lexer			*redir;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

int		check_quotes(char *str);
int		is_cmd(t_lexer_type type);
int		is_quote(t_lexer_type type);
int		add_count_elem(char **data);
int		lex_error(t_lexer *head);
int		pipes_err(t_lexer *head);
int		is_redirection(t_lexer_type type);
void	handle_redirection(t_lexer **token, t_cmd *cmd);
void	redir_handler(t_lexer **token, char **str);
void	space_handler(t_lexer **tokens, char **str);
void	remove_space_in_cmd(t_cmd **head);
void    init_signals(void);
void	print_error(char *error, char *token);
int	handle_number(char **input, int *i, char *tmp, char *tmp2);
int	loop_while_dollar(char **input, char **tmp, int i, char *tmp2);
char	*build_res(char *res, int i, int j, char **input);
void	add_to_cmd(char *data, t_cmd *current);
char	**env_find(char *input);
char	*build_res(char *res, int i, int j, char **input);
void	init_temp(char **tmp, char **tmp2);
char	**add_data_to_tab(char *data);
void	remove_space_tokens(t_lexer **head);
void	add_index_to_token(t_lexer *tokens);
void	pipe_handler(t_lexer **tokens, char **str);
t_cmd	*parser(t_lexer **tokens);
void	handle_env_value(char **res, char *tmp, int *i);
void	fill_nbr_element(t_cmd **parsing);
t_cmd	*create_new_cmd(void);
t_lexer	*find_last(t_lexer *node);
void	fill_nbr_element(t_cmd **parsing);

#endif