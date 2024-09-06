/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 10:51:59 by kali              #+#    #+#             */
/*   Updated: 2024/09/06 10:53:01 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "../libft/libft.h"
# define SPACE_CHAR "|<>"
# define IS_TOKEN "\"'|<>"

// Token types
typedef enum s_token_type
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
typedef struct s_token
{
	t_lexer_type type;
	int		index;
	char	*data;
	struct s_token *next;
	struct s_token *prev;
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
t_lexer	*find_last(t_lexer *node);
#endif