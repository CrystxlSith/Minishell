/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 10:51:59 by kali              #+#    #+#             */
/*   Updated: 2024/09/08 15:17:23 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "../libft/libft.h"
# define SPACE_CHAR "|<>"
# define IS_TOKEN "\"'|<>"

// Token types
typedef enum s_lexer_type
{
	E_CMD, //*str
	E_ARG,
	E_REDIR_IN,
	E_REDIR_OUT,
	E_OPTIONS,
	E_REDIR_DEL,
	E_REDIR_APP,
	E_PIPE,
	E_S_QUOTE,
	E_D_QUOTE,
	E_UNKNOWN,
	END,
}	t_lexer_type;


// Token structure
typedef struct s_lexer
{
	t_lexer_type type;
	int		index;
	char	*data;
	struct s_lexer *next;
	struct s_lexer *prev;
}	t_lexer;

// Parse in command, separated by pipes
typedef struct	s_cmd
{
	char	**str;
	int		redir_nb;
	char	*here_doc;
	t_lexer	*redir;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

void add_index_to_token(t_lexer *tokens);
t_cmd	*parser(t_lexer **tokens);
void	print_lexers(t_lexer *head);
void	print_info(t_cmd *parsed_cmd);
t_cmd *create_new_cmd();
int	is_redirection(t_lexer_type type);
void	handle_redirection(t_lexer *token, t_cmd *cmd);




t_lexer	*find_last(t_lexer *node);
#endif