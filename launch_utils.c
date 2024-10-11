/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:18:05 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/11 13:34:47 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_minishell	minishell;

int	ft_remove(const char *pathname)
{
	struct stat	path_stat;

	if (lstat(pathname, &path_stat) == -1)
		return (-1);
	else
	{
		if (unlink(pathname) == -1)
			return (-1);
	}
	return (0);
}

char	*launch_minishell(t_env *data, char *name)
{
	minishell.line_read = readline(name);
	if (minishell.line_read == NULL)
	{
		free(minishell.line_read);
		return (NULL);
		exit (1);
	}
	if (minishell.line_read[0] == '\0')
	{
		free(minishell.line_read);
	}
	return (minishell.line_read);
}

int	heredoc(t_env *data, t_cmd *parsing)
{
	t_lexer	*tokens_hdc;
	t_cmd	*token_input;

	minishell.line_read = launch_minishell(data, "> ");
	tokens_hdc = tokenize(minishell.line_read);
	token_input = parser(&tokens_hdc);
	fill_input_hdc(&tokens_hdc, &parsing, &data);
	return (0);
}

