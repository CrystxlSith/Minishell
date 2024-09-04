/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 10:51:59 by kali              #+#    #+#             */
/*   Updated: 2024/09/04 14:21:14 by jopfeiff         ###   ########.fr       */
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
	E_CMD,
	E_ARG,
	E_REDIR_IN,
	E_REDIR_OUT,
	E_OPTIONS,
	E_REDIR_DEL,
	E_REDIR_APP,
	E_PIPE,
	E_ENV,
	E_S_QUOTE,
	E_D_QUOTE,
	// E_SPACES,
	E_UNKNOWN,
}	t_token_type;

// Token structure
typedef struct s_token
{
	t_token_type type;
	char	*data;
	struct s_token *next;
	struct s_token *prev;
}	t_token;

#endif