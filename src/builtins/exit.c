/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:17:27 by agiliber          #+#    #+#             */
/*   Updated: 2024/11/04 15:19:15 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_exit_err(char *str, t_lexer *tokens,\
 t_cmd *cmd_parsing, t_env *data)
{
	ft_putstr_fd("exit\n", STDERR_FILENO);
	ft_putstr_fd("minishell : exit: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	free_all_line(tokens, cmd_parsing);
	free_minishell(data);
}

char	**ft_array_dup(char **str)
{
	int		i;
	char	**res;

	i = 0;
	res = NULL;
	while (str[i])
		i++;
	res = malloc(sizeof(char *) * (i + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (str[i])
	{
		res[i] = ft_strdup(str[i]);
		i++;
	}
	res[i] = NULL;
	return (res);
}

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	exit_code(char **str)
{
	int		code;

	if (!str[1])
		code = g_sig_status;
	else
		code = ft_atoi(str[1]);
	ft_free_array(str);
	exit(code);
}

int	ft_exit_shell(t_cmd *cmd_parsing, t_env *data, t_lexer *tokens)
{
	char	**str;

	if (cmd_parsing->str[1] && ft_atoi(cmd_parsing->str[1]) == INT_MAX)
	{
		print_exit_err(cmd_parsing->str[1], tokens, cmd_parsing, data);
		exit(2);
	}
	if (cmd_parsing->str[1] && cmd_parsing->str[2])
	{
		ft_putstr_fd(EXIT_ARGS_ERR, STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	str = ft_array_dup(cmd_parsing->str);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	free_all_line(tokens, cmd_parsing);
	free_minishell(data);
	exit_code(str);
	return (g_sig_status);
}
