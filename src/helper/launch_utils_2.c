/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycry <crycry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 02:59:42 by crycry            #+#    #+#             */
/*   Updated: 2024/10/31 03:28:13 by crycry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	launcher_exec(char *input, t_env **data)
{
	if (input == NULL)
	{
		free_minishell(*data);
		clear_history();
		return (-1);
	}
	return (0);
}

int	check_if_redir(t_cmd **parsing)
{
	t_cmd	*tmp;
	int		count;

	count = 0;
	tmp = *parsing;
	while (tmp)
	{
		if (tmp->redir != NULL)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

int	check_cmd_parsing(t_cmd **parsing, t_env **data)
{
	char	*path;
	int		trigger;

	trigger = 0;
	if (detect_hdc(parsing) != 0 || check_if_redir(parsing) != 0)
		return (0);
	if (access((*parsing)->str[0], X_OK) != -1)
		trigger++;
	path = get_filepath((*parsing)->str, (*data)->var);
	if (path != NULL)
		trigger++;
	if (check_if_builtins((*parsing)->str[0]) != -1)
	{
		g_sig_status = 0;
		trigger++;
	}
	if (trigger == 0)
	{
		free(path);
		ft_printf_fd(2, "bash: %s:command not found\n", (*parsing)->str[0]);
		g_sig_status = 127;
		return (-1);
	}
	free(path);
	return (0);
}

int	start_error(char *input)
{
	if (!input)
		exit(EXIT_FAILURE);
	else if (input[0] == '\0')
	{
		free(input);
		return (1);
	}
	else if (lex_error(input))
	{
		free(input);
		return (1);
	}
	return (0);
}