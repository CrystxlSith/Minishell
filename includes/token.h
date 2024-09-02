/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 10:51:59 by kali              #+#    #+#             */
/*   Updated: 2024/09/02 16:38:54 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "../libft/libft.h"
# define SPACE_CHAR "|<>"

// Enumeration des types de token
typedef enum s_token_type
{
	E_CMD,
	E_ARG,
	E_REDIR_IN,
	E_REDIR_OUT,
	E_OPTIONS,
	E_REDIR_APP,
	E_PIPE,
	E_ENV,
	E_S_QUOTE,
	E_D_QUOTE,
	E_SPACES,
	E_UNKNOWN,
}	t_token_type;

typedef struct s_token
{
	t_token_type type;
	char	*data;
	struct s_token *next;
}	t_token;

#endif