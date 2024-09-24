/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 10:51:59 by kali              #+#    #+#             */
/*   Updated: 2024/09/24 15:15:56 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "../libft/libft.h"
# include "minishell.h"
# include "builtins.h"
# include <stdbool.h>
# include <limits.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# define BUFFER_SIZE 1024
# define SPACE_CHAR "|<>"
# define IS_TOKEN "\"'|<>&"
# define IS_REDIRECTION "<>"

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
	t_lexer_type 	type;
	int				index;
	char			*data;
	struct s_lexer *next;
	struct s_lexer *prev;
}					t_lexer;

// Parse in command, separated by pipes
typedef struct	s_cmd
{
	int				redir_nb;
	int				index;
	int				elem_nb;
	char			**str;
	char			**only_cmd;
	char			*here_doc;
	t_lexer			*redir;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

t_cmd	*parser(t_lexer **tokens);
int	is_cmd(t_lexer_type type);
void	handle_env_var(char **input, char **new_input, int *i, int *k);
void	copy_env_value(char *env_value, char **new_input, int *k);
void	copy_var_name(char **input, char **new_input, int *i, int *k, int l);
int	is_quote(t_lexer_type type);
void	add_index_to_token(t_lexer *tokens);
int lex_error_handler(t_lexer *tokens);
int	pipes_err(t_lexer *head);
void	print_lexers(t_lexer *head);
void	print_info(t_cmd *parsed_cmd);
int		check_synthax_error(t_lexer *tokens);
t_cmd	*create_new_cmd();
int	add_count_elem(char **data);
int lex_error(t_lexer *head);
int		is_redirection(t_lexer_type type);
void	handle_redirection(t_lexer *token, t_cmd *cmd);
void	redir_handler(t_lexer **token, char **str);
void	space_handler(t_lexer **tokens, char **str);
void	pipe_handler(t_lexer **tokens, char **str);
t_lexer	*find_last(t_lexer *node);
void	fill_nbr_element(t_cmd **parsing);
void free_tokens(t_lexer *tokens);

#endif