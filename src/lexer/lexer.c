/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:01:08 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/10/11 16:46:48 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	quotes_handler(t_lexer **tokens, char **str)
{
	char	quote;
	char	*start;
	char	*content;

	quote = **str;
	start = ++(*str);
	while (**str && **str != quote)
		(*str)++;
	content = ft_substr(start, 0, *str - start);
	if (**str == quote)
	{
		if (quote == '\'')
			create_new_token(E_S_QUOTE, content, tokens);
		else
			create_new_token(E_D_QUOTE, content, tokens);
		(*str)++;
	}
	else
		create_new_token(E_UNKNOWN, \
			ft_strjoin(ft_strdup(start - 1), content), tokens);
	free(content);
}

static int	check_tokens(char **str, t_lexer **tokens)
{
	char	unknown[2];

	if (**str == '|')
		return (pipe_handler(tokens, str), 1);
	else if (ft_strchr(IS_REDIRECTION, **str))
		return (redir_handler(tokens, str), 1);
	else if (**str == '\'' || **str == '"')
		return (quotes_handler(tokens, str), 1);
	else if (**str == '&')
	{
		if (*(*str + 1) == '&')
			return (create_new_token(E_AMPERSAND, "&&", tokens), \
				(*str) += 2, 1);
		else
			return (create_new_token(E_AMPERSAND, "&", tokens), (*str)++, 1);
	}
	else if (!strchr(IS_TOKEN, **str) && !ft_isspace(**str))
	{
		unknown[0] = **str;
		unknown[1] = '\0';
		return (create_new_token(E_UNKNOWN, unknown, tokens), (*str)++, 1);
	}
	return (0);
}

static void	check_cmd(char **str, t_lexer **tokens)
{
	int		i;
	char	*cmd;

	i = 0;
	cmd = ft_strdup(*str);
	while (**str && !ft_isspace(**str) && !ft_strchr(IS_TOKEN, **str))
	{
		(*str)++;
		i++;
	}
	cmd[i] = '\0';
	create_new_token(E_CMD, cmd, tokens);
	free(cmd);
}

void	check_options(char **str, t_lexer **tokens)
{
	int		i;
	char	*options;

	i = 0;
	options = ft_strdup(*str);
	while (**str && !ft_isspace(**str) && !ft_strchr(IS_TOKEN, **str))
	{
		if (ft_strchr(IS_TOKEN, **str))
			break ;
		(*str)++;
		i++;
	}
	options[i] = '\0';
	create_new_token(E_OPTIONS, options, tokens);
	free(options);
}

t_lexer	*tokenize(char *str)
{
	t_lexer	*tokens;

	tokens = NULL;
	while (*str && ft_isspace(*str))
		str++;
	if (!check_quotes(str))
	{
		while (*str)
		{
			if (ft_isspace(*str))
				space_handler(&tokens, &str);
			else if (*str && ft_isascii(*str) && !ft_strchr(IS_TOKEN, *str) && \
				*str != '-')
				check_cmd(&str, &tokens);
			else if (*str && *str == '-')
				check_options(&str, &tokens);
			else if (*str && check_tokens(&str, &tokens))
				continue ;
			else
				str++;
		}
	}
	add_index_to_token(tokens);
	return (tokens);
}
